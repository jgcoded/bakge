# Bakge CMake file

cmake_minimum_required (VERSION 2.6)

project(BAKGE)

# Version of GLFW we're using
set(BAKGE_GLFW_VERSION "3.0")
set(BAKGE_GLFW_VERSION_FULL "3.0.0")
message("-- Bakge using GLFW version ${GLFW_VERSION_FULL}")

set(BAKGE_SDK_PATH "sdk")
set(BAKGE_LIB_DIR "lib")
set(BAKGE_BIN_DIR "bin")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules/")

# Common required packages
find_package(OpenGL)

set(BAKGE_GLFW_PATH ${BAKGE_SOURCE_DIR}/lib/glfw-3.0)

# Bakge include/link directories
set(BAKGE_INCLUDE_DIRECTORIES ${BAKGE_SOURCE_DIR}/include)
set(BAKGE_LIBRARY_DIRECTORIES ${BAKGE_SOURCE_DIR}/lib)

# Append common directories
list(APPEND BAKGE_INCLUDE_DIRECTORIES ${OPENGL_INCLUDE_DIR})
list(APPEND BAKGE_INCLUDE_DIRECTORIES ${BAKGE_GLFW_PATH}/include)

# Output all generated libraries and binaries to the SDK dir
set(BAKGE_TARGET_DIR ${BAKGE_SOURCE_DIR}/${BAKGE_SDK_PATH})
set(BAKGE_SDK_LIB_PATH ${BAKGE_TARGET_DIR}/${BAKGE_LIB_DIR})
set(BAKGE_SDK_BIN_PATH ${BAKGE_TARGET_DIR}/${BAKGE_BIN_DIR})
set(BAKGE_SDK_EXAMPLES_OUTPUT_PATH ${BAKGE_SDK_BIN_PATH}/example)
set(BAKGE_SDK_TESTS_OUTPUT_PATH ${BAKGE_SDK_BIN_PATH}/test)

# We want ALL libraries (event external ones)to build into the
# SDK's library directory
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${BAKGE_TARGET_DIR}/${BAKGE_LIB_DIR})


# Append SDK directories so Bakge examples and tests can build against them
list(APPEND BAKGE_LIBRARY_DIRECTORIES ${BAKGE_SDK_LIB_PATH})


# Set required library vars

if(UNIX AND NOT APPLE)
  find_package(X11 REQUIRED)
  list(APPEND BAKGE_INCLUDE_DIRECTORIES ${X11_INCLUDE_DIR})
  list(APPEND BAKGE_LIBRARY_DIRECTORIES ${X11_LIBRARY_DIR})
  set(BAKGE_LIBRARIES
    m
    glfw3
    GL
    GLU
    ${X11_X_PRE_LIBS}
    ${X11_LIBRARIES}
    ${X11_X_EXTRA_LIBRARIES}
    Xrandr
    Xi
    pthread
  )
endif()

if(UNIX AND APPLE)
  find_package(X11 REQUIRED)
  FIND_LIBRARY(COCOA_LIBRARY Cocoa)
  FIND_LIBRARY(IOKIT_LIBRARY IOKit)
  FIND_LIBRARY(AGL_LIBRARY AGL)
  FIND_LIBRARY(CORE_FOUNDATION_LIBRARY CoreFoundation)
  list(APPEND BAKGE_INCLUDE_DIRECTORIES ${Cocoa_INCLUDE_DIRS})
  list(APPEND CMAKE_CXX_FLAGS -ObjC++)
  set(BAKGE_LIBRARIES
    m
    glfw3
    GL
    GLU
    ${COCOA_LIBRARY}
    ${IOKIT_LIBRARY}
    ${CORE_FOUNDATION_LIBRARY}
    ${AGL_LIBRARY}
  )
endif()

if(WIN32)
  set(BAKGE_LIBRARIES
    opengl32.lib
    gdi32.lib
    user32.lib
    glu32.lib
    winmm.lib
    glfw3
  )
endif(WIN32)

foreach(directory ${BAKGE_INCLUDE_DIRECTORIES})
  include_directories(${directory})
endforeach(directory)

foreach(directory ${BAKGE_LIBRARY_DIRECTORIES})
  link_directories(${directory})
endforeach(directory)

add_subdirectory(lib)
add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(example)
