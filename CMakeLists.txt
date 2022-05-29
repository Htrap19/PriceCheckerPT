cmake_minimum_required(VERSION 3.19)
project(PriceChecker)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DPC_DEBUG)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_definitions(-DPC_RELEASE)
endif()

if (WIN32)
    add_definitions(-DPC_PLATFORM_WINDOWS)
elseif(UNIX)
    add_definitions(-DPC_PLATFORM_UNIX)
endif()

set(CMAKE_CXX_STANDARD 17)
add_subdirectory(vendor)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED IMPORTED_TARGET "gtkmm-4.0")
pkg_check_modules(CURL REQUIRED IMPORTED_TARGET "libcurl")

include_directories(src vendor/curlpp/include vendor/gumbo_parser/src vendor/gumbo_query/src vendor/json_cpp/include vendor/stb)
add_executable(PriceChecker vendor/stb/stb_image.cpp main.cpp src/components/Window.cpp src/components/Window.h src/components/stores/ContinenteContent.cpp src/components/stores/ContinenteContent.h src/components/stores/AuchanContent.cpp src/components/stores/AuchanContent.h src/components/ProductComponent.cpp src/components/ProductComponent.h src/utils/Searchable.h src/utils/Fetchable.h src/components/InfoBar.cpp src/components/InfoBar.h src/utils/FileCacheManager.cpp src/utils/FileCacheManager.h src/components/RootContent.cpp src/components/RootContent.h src/utils/CssProvider.h src/utils/CssProvider.cpp src/components/HeaderBar.cpp src/components/HeaderBar.h src/components/EmptyList.cpp src/components/EmptyList.h src/utils/TaskQueue.cpp src/utils/TaskQueue.h src/utils/Fetchable.cpp src/utils/Utils.cpp src/utils/Utils.h src/components/stores/MiniprecoContent.cpp src/components/stores/MiniprecoContent.h src/components/SearchableContent.cpp src/components/SearchableContent.h src/components/stores/ElcorteinglesContent.cpp src/components/stores/ElcorteinglesContent.h src/utils/Searchable.cpp src/utils/LanguageManager.cpp src/utils/LanguageManager.h src/utils/ConfigManager.cpp src/utils/ConfigManager.h src/components/stores/SparContent.cpp src/components/stores/SparContent.h src/utils/UIQueue.cpp src/utils/UIQueue.h src/components/CompareComponent.cpp src/components/CompareComponent.h src/utils/AssetManager.cpp src/utils/AssetManager.h)

# ld command
set(ld_command ld -r -b binary)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/assets)

# compile lang_packs
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/assets/lang_packs)
file(GLOB_RECURSE lang_packs_json_list assets/lang_packs/*.json)
foreach(file ${lang_packs_json_list})
    get_filename_component(lang_file_name ${file} NAME)
    get_filename_component(lang_file_path ${file} DIRECTORY)
    set(output_file ${CMAKE_BINARY_DIR}/assets/lang_packs/${lang_file_name}.o)
    file(TOUCH ${output_file})
    add_custom_command(TARGET PriceChecker
            PRE_BUILD
            COMMAND cd ${lang_file_path} && ${ld_command} ${lang_file_name} -o ${output_file})
    set(lang_packs_compiled_list ${lang_packs_compiled_list} ${output_file})
endforeach()

# assets
file(GLOB_RECURSE assets_list assets/image/*.* assets/styles/*.css assets/.default_config.json)
foreach(asset ${assets_list})
    get_filename_component(asset_name ${asset} NAME)
    get_filename_component(asset_path ${asset} DIRECTORY)
    set(asset_output_file ${CMAKE_BINARY_DIR}/assets/${asset_name}.o)
    file(TOUCH ${asset_output_file})
    add_custom_command(TARGET PriceChecker
            PRE_BUILD
            COMMAND cd ${asset_path} && ${ld_command} ${asset_name} -o ${asset_output_file})
    set(asset_list ${asset_list} ${asset_output_file})
endforeach()
target_link_libraries(PriceChecker curlpp gumbo_query json_cpp PkgConfig::GTKMM ${CURL_STATIC_LIBRARIES} ${lang_packs_compiled_list} ${asset_list})