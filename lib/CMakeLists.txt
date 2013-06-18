cmake_minimum_required (VERSION 2.6)

# Downloads GLFW if needed
include(${BAKGE_SOURCE_DIR}/cmake/GetGLFW.cmake)

# Downloads Lua if needed
include(${BAKGE_SOURCE_DIR}/cmake/GetLua.cmake)
include(${BAKGE_SOURCE_DIR}/cmake/BuildLua.cmake)

# Build GLFW
set(GLFW_CLIENT_LIBRARY "opengl")
add_subdirectory(glfw-3.0)

