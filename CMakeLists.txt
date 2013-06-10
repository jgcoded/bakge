# Bakge CMake file

cmake_minimum_required (VERSION 2.6)

project (BAKGE)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

include_directories(${BAKGE_SOURCE_DIR}/include)

if(UNIX)
  find_package(X11 REQUIRED)
  include_directories(${X11_INCLUDE_DIR})
endif(UNIX)


if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  find_package(X11 REQUIRED)
  include_directories(${X11_INCLUDE_DIR})
endif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

find_package(OpenGL)
include_directories(${OPENGL_INCLUDE_DIR})

# Set output directory of the static library
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_subdirectory(src)
add_subdirectory(test)

