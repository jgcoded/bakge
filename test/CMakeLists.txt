# Bakge unit tests CMake file

cmake_minimum_required(VERSION 2.6)

include_directories(${BAKGE_SOURCE_DIR}/include)

set(TESTS
  texture
  types
  window
)

if(UNIX)
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
endif(UNIX)


if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  find_package(X11 REQUIRED)
  include_directories(${X11_INCLUDE_DIR})
  link_directories(${X11_LIBRARY_DIR})
  set(CORELIBS
    m
    ${X11_X_PRE_LIBS}
    ${X11_LIBRARIES}
    ${X11_X_EXTRA_LIBRARIES}
    ${GL_LIBRARY}
  )
endif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")


if(WIN32)
  set(CORELIBS
    user32.lib
    gdi32.lib
    opengl32.lib
    glu32.lib
    winmm.lib
  )
endif(WIN32)


foreach(test ${TESTS})
  add_executable(${test} ${test}.cpp)
  target_link_libraries(${test} bakge ${CORELIBS})
endforeach(test)
