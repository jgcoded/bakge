# Bakge CMake file

cmake_minimum_required (VERSION 2.6)

project (BAKGE)

include_directories(${BAKGE_SOURCE_DIR}/include)

add_subdirectory(src)
add_subdirectory(test)

