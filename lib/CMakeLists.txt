cmake_minimum_required (VERSION 2.6)

# Downloads external libraries if needed
include(${BAKGE_SOURCE_DIR}/cmake/GetGLFW.cmake)
include(${BAKGE_SOURCE_DIR}/cmake/GetLua.cmake)
include(${BAKGE_SOURCE_DIR}/cmake/GetGLEW.cmake)
include(${BAKGE_SOURCE_DIR}/cmake/GetOpenAL.cmake)
include(${BAKGE_SOURCE_DIR}/cmake/GetPhysFS.cmake)

# Build GLFW with our modified CMake build
set(GLFW_CLIENT_LIBRARY "opengl")
add_subdirectory(glfw-3.0)

# Build PhysFS 2.0.3 (has its own CMake build)
SET(PHYSFS_BUILD_TEST CACHE BOOL FALSE FORCE)
add_subdirectory(physfs-2.0.3)

# OpenAL thinks CMAKE_SOURCE_DIR is its root dir. Trick it!
set(CMAKE_SOURCE_DIR ${BAKGE_SOURCE_DIR}/lib/openal-1.15.1)
add_subdirectory(${OPENAL_TARGET})
set(CMAKE_SOURCE_DIR ${BAKGE_SOURCE_DIR})

# Builds external libraries
include(${BAKGE_SOURCE_DIR}/cmake/BuildLua.cmake)
include(${BAKGE_SOURCE_DIR}/cmake/BuildGLEW.cmake)
