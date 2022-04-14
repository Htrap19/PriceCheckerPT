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

include_directories(src vendor/curlpp/include vendor/gumbo_parser/src vendor/gumbo_query/src)
add_executable(PriceChecker main.cpp src/components/Window.cpp src/components/Window.h src/components/ContinenteContent.cpp src/components/ContinenteContent.h src/components/AuchanContent.cpp src/components/AuchanContent.h src/components/ProductComponent.cpp src/components/ProductComponent.h src/utils/Searchable.h src/utils/Fetchable.h src/components/InfoBar.cpp src/components/InfoBar.h src/utils/FileCacheManager.cpp src/utils/FileCacheManager.h src/components/RootContent.cpp src/components/RootContent.h src/utils/CssProvider.h src/utils/CssProvider.cpp src/components/HeaderBar.cpp src/components/HeaderBar.h src/components/EmptyList.cpp src/components/EmptyList.h src/utils/TaskQueue.cpp src/utils/TaskQueue.h src/utils/Fetchable.cpp src/utils/Utils.cpp src/utils/Utils.h src/components/MiniprecoContent.cpp src/components/MiniprecoContent.h src/components/SearchableContent.cpp src/components/SearchableContent.h src/components/ElcorteinglesContent.cpp src/components/ElcorteinglesContent.h)
target_link_libraries(PriceChecker curlpp gumbo_query PkgConfig::GTKMM ${CURL_STATIC_LIBRARIES})