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