# Bakge CMake file

cmake_minimum_required (VERSION 2.6)

project(BAKGE)

# Prevent build attempts on any unsupported platform
if(NOT APPLE AND NOT WIN32 AND NOT UNIX)
  message(FATAL_ERROR "Bakge only builds on Windows, OS X or Linux")
endif()

# Version of GLFW we're using
set(BAKGE_GLFW_VERSION "3.0")
set(BAKGE_GLFW_VERSION_FULL "3.0.0")
message("-- Bakge using GLFW version ${GLFW_VERSION_FULL}")

set(BAKGE_SDK_PATH "sdk")
set(BAKGE_LIB_DIR "lib")
set(BAKGE_BIN_DIR "bin")
set(BAKGE_INC_DIR "include")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules/")

# Common required packages
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

# Bakge include/link directories
set(BAKGE_INCLUDE_DIRECTORIES ${BAKGE_SOURCE_DIR}/include)
set(BAKGE_LIBRARY_DIRECTORIES ${BAKGE_SOURCE_DIR}/lib)

# Append library include directories
# SDK build needs to copy them into the SDK directory
# Note: Lua has a special build and headers copy
set(BAKGE_GLFW_PATH ${BAKGE_SOURCE_DIR}/lib/glfw-3.0)
set(BAKGE_GLEW_PATH ${BAKGE_SOURCE_DIR}/lib/glew-1.9.0)
list(APPEND BAKGE_INCLUDE_DIRECTORIES ${BAKGE_GLFW_PATH}/include)
list(APPEND BAKGE_INCLUDE_DIRECTORIES ${BAKGE_GLEW_PATH}/include)

# Output all generated libraries and binaries to the SDK dir
set(BAKGE_TARGET_DIR ${BAKGE_SOURCE_DIR}/${BAKGE_SDK_PATH})
set(BAKGE_SDK_INC_PATH ${BAKGE_TARGET_DIR}/${BAKGE_INC_DIR})
set(BAKGE_SDK_LIB_PATH ${BAKGE_TARGET_DIR}/${BAKGE_LIB_DIR})
set(BAKGE_SDK_BIN_PATH ${BAKGE_TARGET_DIR}/${BAKGE_BIN_DIR})

# If not on Visual Studio, enable a simple debug/release build target
if(NOT MSVC)
  option(DEBUG_BUILD "Build with debug symbols and definitions" ON)
  if(DEBUG_BUILD)
    add_definitions(-D_DEBUG)
    set(BAKGE_SDK_LIB_PATH ${BAKGE_SDK_LIB_PATH}/Debug)
    set(BAKGE_SDK_BIN_PATH ${BAKGE_SDK_BIN_PATH}/Debug)
  else()
    set(BAKGE_SDK_LIB_PATH ${BAKGE_SDK_LIB_PATH}/Release)
    set(BAKGE_SDK_BIN_PATH ${BAKGE_SDK_BIN_PATH}/Release)
  endif()
endif()

# Now set our paths
set(BAKGE_SDK_EXAMPLES_OUTPUT_PATH ${BAKGE_SDK_BIN_PATH}/example)
set(BAKGE_SDK_TESTS_OUTPUT_PATH ${BAKGE_SDK_BIN_PATH}/test)

# We want ALL libraries (event external ones)to build into the
# SDK's library directory
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${BAKGE_SDK_LIB_PATH})


########################################
# PLATFORM SPECIFIC LIBRARIES SETUP
########################################

if(UNIX AND NOT APPLE)
  find_package(X11 REQUIRED)
  include_directories(${X11_INCLUDE_DIR})
  include_directories(${X11_LIBRARY_DIR})
  set(BAKGE_LIBRARIES
    m
    glew
    glfw3
    lua
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
  FIND_LIBRARY(COCOA_LIBRARY Cocoa)
  FIND_LIBRARY(IOKIT_LIBRARY IOKit)
  FIND_LIBRARY(AGL_LIBRARY AGL)
  FIND_LIBRARY(CORE_FOUNDATION_LIBRARY CoreFoundation)
  include_directories(${Cocoa_INCLUDE_DIRS})
  FIND_LIBRARY(OPENGL_LIBRARY OpenGL)
  set(BAKGE_LIBRARIES
    m
    glew
    glfw3
    lua
    ${OPENGL_LIBRARY}
    ${COCOA_LIBRARY}
    ${IOKIT_LIBRARY}
    ${CORE_FOUNDATION_LIBRARY}
    ${AGL_LIBRARY}
  )
endif()

if(WIN32)
  set(BAKGE_LIBRARIES
    gdi32.lib
    user32.lib
    winmm.lib
    glew
    glfw3
    lua
    glu32.lib
    opengl32.lib
    ws2_32.lib
  )
endif(WIN32)

########################################
# BAKGE INCLUDE/LIB PATHS
########################################

# Add include directories
foreach(directory ${BAKGE_INCLUDE_DIRECTORIES})
  include_directories(${directory})
endforeach(directory)

foreach(directory ${BAKGE_LIBRARY_DIRECTORIES})
  link_directories(${directory})
endforeach(directory)

# Also add SDK paths
include_directories(${BAKGE_SDK_INC_PATH})
link_directories(${BAKGE_SDK_LIB_PATH})


########################################
# BAKGE CMAKE SUBDIRECTORIES
########################################

# Downloads and builds external library dependencies
add_subdirectory(lib)

# Compile Bakge library
add_subdirectory(src)

# Compiles Bakge unit tests
add_subdirectory(test)

# Compiles example Bakge programs
add_subdirectory(example)


########################################
# BAKGE SDK BUILD
########################################

# Copy Bakge headers and library headers to SDK dir
# Doesn't copy OpenGL or platform-specific headres like windows.h or x11.h
make_directory(${BAKGE_TARGET_DIR})
make_directory(${BAKGE_SDK_INC_PATH})
foreach(include_dir ${BAKGE_INCLUDE_DIRECTORIES})
  execute_process(COMMAND ${CMAKE_COMMAND} -E copy_directory ${include_dir}
                                                    ${BAKGE_SDK_INC_PATH})
endforeach(include_dir)

###
# ! NOTE: Lua headers are copied separately before the build, since
# their build generates an include/ directory with necessary headers.
# As such Lua include directories aren't appended to the
# BAKGE_INCLUDE_DIRECTORIES list.
# Instead, Bakge copies these headers to the SDK before
# building its library, and compiles with the SDK's include path
# to resolve any potential include path inconsistencies.
# e.g. #include <lua/lua.h>   vs   #include <lua.h>
###

