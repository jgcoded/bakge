cmake_minimum_required (VERSION 2.6)

# Downloads external libraries if needed
include(${BAKGE_SOURCE_DIR}/cmake/GetGLFW.cmake)
include(${BAKGE_SOURCE_DIR}/cmake/GetLua.cmake)
include(${BAKGE_SOURCE_DIR}/cmake/GetGLEW.cmake)

# Build GLFW (has its own CMake build)
set(GLFW_CLIENT_LIBRARY "opengl")
add_subdirectory(glfw-3.0)

# Builds external libraries
include(${BAKGE_SOURCE_DIR}/cmake/BuildLua.cmake)
include(${BAKGE_SOURCE_DIR}/cmake/BuildGLEW.cmake)
