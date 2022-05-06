# curlpp
add_definitions(-DCURL_STATICLIB)
file(GLOB_RECURSE HeaderFileList curlpp/include/*)
file(GLOB_RECURSE SourceFileList curlpp/src/*)
add_library(curlpp STATIC ${HeaderFileList} ${SourceFileList})
target_include_directories(curlpp PUBLIC curlpp/include)

# gumbo_parser
file(GLOB_RECURSE gumboFileList gumbo_parser/src/*)
add_library(gumbo_parser STATIC ${gumboFileList})
target_include_directories(gumbo_parser PUBLIC gumbo_parser/src)

# gumbo_query
file(GLOB_RECURSE gumboFileList gumbo_query/src/*.cpp)
add_library(gumbo_query STATIC ${gumboFileList})
target_include_directories(gumbo_query PUBLIC gumbo_parser/src)
target_link_libraries(gumbo_query gumbo_parser)

# json_cpp
file(GLOB_RECURSE jsonCppFileList json_cpp/src/*.cpp json_cpp/src/*.h)
add_library(json_cpp STATIC ${jsonCppFileList})
target_include_directories(json_cpp PUBLIC json_cpp/include)