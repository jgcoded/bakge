cmake_minimum_required (VERSION 2.6)

# Downloads GLFW if needed
include(${BAKGE_SOURCE_DIR}/cmake/GetGLFW.cmake)

# Build GLFW
set(GLFW_CLIENT_LIBRARY "opengl")
add_subdirectory(glfw-3.0)

