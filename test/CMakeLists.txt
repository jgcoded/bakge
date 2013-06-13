# Bakge unit tests CMake file

cmake_minimum_required(VERSION 2.6)

include_directories(${BAKGE_SOURCE_DIR}/include)

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
)

if(UNIX AND NOT APPLE)
  find_package(X11 REQUIRED)
  include_directories(${X11_INCLUDE_DIR})
  link_directories(${X11_LIBRARY_DIR})
  set(CORELIBS
    m
    ${X11_X_PRE_LIBS}
    ${X11_LIBRARIES}
    ${X11_X_EXTRA_LIBRARIES}
    GL
    GLU
  )
endif()


if(UNIX AND APPLE)
  find_package(X11 REQUIRED)
  FIND_LIBRARY(COCOA_LIBRARY Cocoa)
  include_directories(${Cocoa_INCLUDE_DIRS})
  set(CORELIBS
    m
    GL
    GLU
    ${COCOA_LIBRARY}
  )
endif()


if(WIN32)
  set(CORELIBS
    opengl32.lib
    gdi32.lib
    user32.lib
    glu32.lib
    winmm.lib
  )
endif(WIN32)


foreach(test ${TESTS})
  add_executable(${test} ${test}.cpp)
  target_link_libraries(${test} bakge ${CORELIBS})
endforeach(test)
