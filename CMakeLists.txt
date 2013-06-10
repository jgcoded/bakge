# Bakge CMake file

cmake_minimum_required (VERSION 2.6)

project (BAKGE)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

include_directories(${BAKGE_SOURCE_DIR}/include)
include_directories(/usr/X11/include)
link_directories(/usr/X11/lib)

find_package(OpenGL)

# Set output directory of the static library
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_subdirectory(src)
add_subdirectory(test)

