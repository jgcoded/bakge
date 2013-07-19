cmake_minimum_required (VERSION 2.6)

# Downloads external libraries if needed
include(${BAKGE_SOURCE_DIR}/cmake/GetGLFW.cmake)
include(${BAKGE_SOURCE_DIR}/cmake/GetLua.cmake)
include(${BAKGE_SOURCE_DIR}/cmake/GetGLEW.cmake)
include(${BAKGE_SOURCE_DIR}/cmake/GetPhysFS.cmake)

# Build GLFW with our modified CMake build
set(GLFW_CLIENT_LIBRARY "opengl")
configure_file(${BAKGE_SOURCE_DIR}/cmake/BuildGLFW.cmake ${GLFW_TARGET}/CMakeLists.txt COPYONLY)
add_subdirectory(glfw-3.0)

# Build PhysFS 2.0.3 (has its own CMake build)
configure_file(${BAKGE_SOURCE_DIR}/cmake/BuildPhysFS.cmake
                    ${PHYSFS_TARGET}/CMakeLists.txt COPYONLY)
add_subdirectory(physfs-2.0.3)

# Builds external libraries
include(${BAKGE_SOURCE_DIR}/cmake/BuildLua.cmake)
include(${BAKGE_SOURCE_DIR}/cmake/BuildGLEW.cmake)
