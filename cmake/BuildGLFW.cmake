
set(GLFW_DIR ${BAKGE_SOURCE_DIR}/lib/glfw-2.7.9)

include_directories(${GLFW_DIR}/include)
include_directories(${GLFW_DIR}/lib)

set(GLFW_SOURCE_DIR ${GLFW_DIR}/lib)

set(GLFW_SOURCES
  ${GLFW_SOURCE_DIR}/enable.c
  ${GLFW_SOURCE_DIR}/fullscreen.c
  ${GLFW_SOURCE_DIR}/glext.c
  ${GLFW_SOURCE_DIR}/image.c
  ${GLFW_SOURCE_DIR}/init.c
  ${GLFW_SOURCE_DIR}/input.c
  ${GLFW_SOURCE_DIR}/joystick.c
  ${GLFW_SOURCE_DIR}/stream.c
  ${GLFW_SOURCE_DIR}/tga.c
  ${GLFW_SOURCE_DIR}/thread.c
  ${GLFW_SOURCE_DIR}/time.c
  ${GLFW_SOURCE_DIR}/window.c
)

if(UNIX AND NOT APPLE)
  list(APPEND GLFW_SOURCES
    ${GLFW_SOURCE_DIR}/x11/x11_enable.c
    ${GLFW_SOURCE_DIR}/x11/x11_fullscreen.c
    ${GLFW_SOURCE_DIR}/x11/x11_glext.c
    ${GLFW_SOURCE_DIR}/x11/x11_init.c
    ${GLFW_SOURCE_DIR}/x11/x11_joystick.c
    ${GLFW_SOURCE_DIR}/x11/x11_keysym2unicode.c
    ${GLFW_SOURCE_DIR}/x11/x11_thread.c
    ${GLFW_SOURCE_DIR}/x11/x11_time.c
    ${GLFW_SOURCE_DIR}/x11/x11_window.c
  )
endif()

add_library(glfw ${GLFW_SOURCES})

