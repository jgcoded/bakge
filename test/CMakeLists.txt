# Bakge unit tests CMake file

cmake_minimum_required(VERSION 2.6)

include_directories(${BAKGE_SOURCE_DIR}/include)

find_package(OpenGL)

set(TESTS
  window
  types
  texture
  glfw
)

if(UNIX)
  set(CORELIBS
    m
    /usr/local/lib/libglfw.a
    X11
    Xrandr
    GL
    GLU
  )
endif(UNIX)


foreach(test ${TESTS})
  add_executable(${test} ${test}.cpp $<TARGET_OBJECTS:BAKGE>)
  target_link_libraries(${test} ${CORELIBS})
endforeach(test)

