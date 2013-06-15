# Bakge unit tests CMake file

cmake_minimum_required(VERSION 2.6)

include_directories(${BAKGE_SOURCE_DIR}/include)
include_directories(${BAKGE_SOURCE_DIR}/lib/glfw-3.0/include)

set(TESTS
  clock
  texture
  types
  window
  node
  vector4
  quaternion
  matrix
  pawn
  loadfile
)


link_directories(${BAKGE_SOURCE_DIR}/lib)

if(UNIX AND NOT APPLE)
  find_package(X11 REQUIRED)
  include_directories(${X11_INCLUDE_DIR})
  link_directories(${X11_LIBRARY_DIR})
  set(CORELIBS
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
  include_directories(${Cocoa_INCLUDE_DIRS})
  list(APPEND CMAKE_CXX_FLAGS -ObjC++)
  set(CORELIBS
    m
    GL
    GLU
    ${COCOA_LIBRARY}
    ${IOKIT_LIBRARY}
    ${CORE_FOUNDATION_LIBRARY}
    ${AGL_LIBRARY}
    glfw3
  )
endif()


if(WIN32)
  set(CORELIBS
    opengl32.lib
    gdi32.lib
    user32.lib
    glu32.lib
    winmm.lib
    glfw3
  )
endif(WIN32)

foreach(test ${TESTS})
  add_executable(${test} ${test}.cpp)
  target_link_libraries(${test} bakge ${CORELIBS})
endforeach(test)

