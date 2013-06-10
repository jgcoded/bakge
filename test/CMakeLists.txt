# Bakge unit tests CMake file

cmake_minimum_required(VERSION 2.6)

include_directories(${BAKGE_SOURCE_DIR}/include)
link_directories(${BAKGE_SOURCE_DIR}/lib)

find_package(OpenGL)
find_package(GLU)

set(TESTS window types texture glfw)

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

