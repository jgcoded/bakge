# Bakge unit tests CMake file

cmake_minimum_required(VERSION 2.6)

include_directories(${BAKGE_SOURCE_DIR}/include)
include_directories(${BAKGE_SOURCE_DIR}/lib/glfw-2.7.9/include)

set(TESTS
  glfw
  texture
  types
  window
)

if(UNIX)
  find_package(GLFW REQUIRED)
  set(CORELIBS
    ${GLFW_LIBRARY}
    m
    X11
    Xrandr
    GL
    GLU
  )
endif(UNIX)


if(WIN32)

  if(MSVC90)
    set(GLFW_LIBRARY ${BAKGE_SOURCE_DIR}/lib/glfw-2.7.9/lib-msvc90/GLFW.lib)
  elseif(MSVC10)
    set(GLFW_LIBRARY ${BAKGE_SOURCE_DIR}/lib/glfw-2.7.9/lib-msvc100/GLFW.lib)
  endif(MSVC90)
  
  set(CORELIBS
    ${GLFW_LIBRARY}
    opengl32.lib
  )
endif(WIN32)


foreach(test ${TESTS})
  add_executable(${test} ${test}.cpp)
  target_link_libraries(${test} ${CORELIBS} bakge)
endforeach(test)
