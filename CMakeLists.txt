cmake_minimum_required(VERSION 3.19)
project(PriceChecker)

set(CMAKE_CXX_STANDARD 17)
add_subdirectory(vendor)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED IMPORTED_TARGET "gtkmm-4.0")
pkg_check_modules(CURL REQUIRED IMPORTED_TARGET "libcurl")

include_directories(src vendor/curlpp/include vendor/gumbo_parser/src vendor/gumbo_query/src)
add_executable(PriceChecker main.cpp src/components/Window.cpp src/components/Window.h src/components/RootVBox.cpp src/components/RootVBox.h src/components/ContentVBox.cpp src/components/ContentVBox.h src/components/ContinenteContent.cpp src/components/ContinenteContent.h src/components/AuchanContent.cpp src/components/AuchanContent.h src/components/ProductComponent.cpp src/components/ProductComponent.h src/helper/Searchable.h src/helper/Fetchable.h src/components/InfoBar.cpp src/components/InfoBar.h)
target_link_libraries(PriceChecker curlpp gumbo_query PkgConfig::GTKMM ${CURL_STATIC_LIBRARIES})