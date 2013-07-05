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

set(BAKGE_SDK_PATH "sdk")
set(BAKGE_LIB_DIR "lib")
set(BAKGE_BIN_DIR "bin")
set(BAKGE_INC_DIR "include")

# Common required packages
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

# Build option
if(NOT MSVC)
  if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release"
                                      "MinSizeRel" "RelWithDebInfo")
  endif()
endif()

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
set(BAKGE_SDK_LIB_PATH ${BAKGE_TARGET_DIR}/${BAKGE_LIB_DIR}/${CMAKE_BUILD_TYPE})
set(BAKGE_SDK_BIN_PATH ${BAKGE_TARGET_DIR}/${BAKGE_BIN_DIR}/${CMAKE_BUILD_TYPE})

# We want ALL libraries (event external ones)to build into the
# SDK's library directory
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${BAKGE_SDK_LIB_PATH})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BAKGE_SDK_BIN_PATH})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BAKGE_SDK_BIN_PATH})

# Bakge options
option(BAKGE_BUILD_TESTS "Build the Bakge test suite" ON)
option(BAKGE_BUILD_EXAMPLES "Build the Bakge examples suite" ON)


########################################
# PLATFORM SPECIFIC LIBRARIES SETUP
########################################

if(UNIX AND NOT APPLE)
  find_package(X11 REQUIRED)
  include_directories(${X11_INCLUDE_DIR})
  include_directories(${X11_LIBRARY_DIR})

  if(BUILD_SHARED_LIBS)
    set(BAKGE_GLFW_LIBRARY glfw)
  else()
    set(BAKGE_GLFW_LIBRARY glfw3)
  endif()

  set(BAKGE_LIBRARIES
    m
    glew
    ${BAKGE_GLFW_LIBRARY}
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

  if(BUILD_SHARED_LIBS)
    set(BAKGE_GLFW_LIBRARY glfw)
  else()
    set(BAKGE_GLFW_LIBRARY glfw3)
  endif()

  set(BAKGE_LIBRARIES
    m
    glew
    ${BAKGE_GLFW_LIBRARY}
    lua
    ${OPENGL_LIBRARY}
    ${COCOA_LIBRARY}
    ${IOKIT_LIBRARY}
    ${CORE_FOUNDATION_LIBRARY}
    ${AGL_LIBRARY}
  )
endif()

if(WIN32)
  FIND_LIBRARY(OPENGL_LIBRARY OpenGL)

  # GLFW has some nuances when it comes to different builds/platforms
  if(BUILD_SHARED_LIBS AND MSVC)
    set(BAKGE_GLFW_LIB glfw3dll)
  else()
    set(BAKGE_GLFW_LIB glfw)
  endif()

  set(BAKGE_LIBRARIES
    glew
    gdi32.lib
    user32.lib
    winmm.lib
    ${BAKGE_GLFW_LIB}
    lua
    glu32.lib
    ${OPENGL_LIBRARY}
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

if(NOT BUILD_SHARED_LIBS)
  link_directories(${BAKGE_SDK_LIB_PATH})
else()
  link_directories(${BAKGE_SDK_BIN_PATH})
endif()

########################################
# BAKGE CMAKE SUBDIRECTORIES
########################################

# Downloads and builds external library dependencies
add_subdirectory(lib)

# Compile Bakge library
add_subdirectory(src)

# Compiles Bakge unit tests
if(BAKGE_BUILD_TESTS)
  add_subdirectory(test)
endif()

# Compiles example Bakge programs
if(BAKGE_BUILD_EXAMPLES)
  add_subdirectory(example)
endif()

# Build the Bakge GDK
add_subdirectory(gdk)


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

