project(Autocomplete)
cmake_minimum_required(VERSION 2.8)
include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/misc.cmake")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/blizzard")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src/")
add_executable(preprocessor
${AC_ROOT_DIR}/src/loader.cpp
${AC_ROOT_DIR}/src/preprocessor.cpp
${AC_ROOT_DIR}/src/tree.cpp
${AC_ROOT_DIR}/src/treeiterator.cpp
${AC_ROOT_DIR}/src/node.cpp
${AC_ROOT_DIR}/src/memusage.cpp
${AC_ROOT_DIR}/src/util/string.cpp
)

add_library(ac MODULE
${AC_ROOT_DIR}/src/plugin.cpp
${AC_ROOT_DIR}/src/tree.cpp
${AC_ROOT_DIR}/src/treeiterator.cpp
${AC_ROOT_DIR}/src/node.cpp
${AC_ROOT_DIR}/src/util/httpparam.cpp
${AC_ROOT_DIR}/src/util/string.cpp
${AC_ROOT_DIR}/src/preprocessor.cpp
${AC_ROOT_DIR}/src/memusage.cpp

)

install (FILES ${AC_ROOT_DIR}/config/blizzard.xml DESTINATION /etc/ac/)


