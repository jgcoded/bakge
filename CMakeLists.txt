# Bakge CMake file

cmake_minimum_required (VERSION 2.6)

project (BAKGE)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

include_directories(${BAKGE_SOURCE_DIR}/include)

find_package(OpenGL)

# On Win32, libs are in root/lib
if(WIN32)
  include_directories(${BAKGE_SOURCE_DIR}/lib/glfw-2.7.9/include)
endif(WIN32)


add_subdirectory(src)
add_subdirectory(test)

