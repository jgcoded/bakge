# Bakge CMake file

cmake_minimum_required (VERSION 2.6)

include_directories(${BAKGE_SOURCE_DIR}/include)
include_directories(${BAKGE_GLFW_PATH}/include)
include_directories(${BAKGE_GLEW_PATH}/include)


########################################
# COMMON HEADERS & MODULES
########################################

set(MODULES
  api/Mutex
  api/Packet
  api/Socket
  api/Thread
  data/SingleNode
  data/LinkedList
  core/Bindable
  core/Drawable
  core/Engine
  core/EventHandler
  core/Renderer
  core/Utility
  core/Window
  engine/ScriptedEngine
  graphics/Mesh
  graphics/Node
  graphics/Pawn
  graphics/Shader
  graphics/ShaderProgram
  graphics/Shape
  graphics/Texture
  graphics/shapes/Sphere
  graphics/shapes/Cone
  graphics/shapes/Cube
  graphics/shapes/Cylinder
  math/Vector3
  math/Vector4
  math/Quaternion
  math/Matrix
  renderer/DeferredGeometryRenderer
  renderer/DeferredLightingRenderer
  renderer/FrontRenderer
)

# Create headers list, add those without a source file
# since they won't get picked up by the following foreach loop
set(HEADERS
  ${BAKGE_SOURCE_DIR}/include/bakge/Bakge
  ${BAKGE_SOURCE_DIR}/include/bakge/math/Math
  ${BAKGE_SOURCE_DIR}/include/bakge/core/Type
)

foreach(module ${MODULES})
  list(APPEND HEADERS ${BAKGE_SOURCE_DIR}/include/bakge/${module})
endforeach(module)


########################################
# PLATFORM MODULES & HEADERS
########################################

if(UNIX AND NOT APPLE)
  set(PLATFORM_PREFIX "x11")
endif()

if(UNIX AND APPLE)
  set(PLATFORM_PREFIX "osx")
  list(APPEND CMAKE_CXX_FLAGS -ObjC++)
endif()

if(WIN32)
  set(PLATFORM_PREFIX "win32")
endif()

set(PLATFORM_MODULES
  clock/${PLATFORM_PREFIX}_Clock
  packet/${PLATFORM_PREFIX}_Packet
  socket/${PLATFORM_PREFIX}_Socket
  thread/${PLATFORM_PREFIX}_Thread
  mutex/${PLATFORM_PREFIX}_Mutex
  utility/${PLATFORM_PREFIX}_Utility
)

# Platform modules might share a common header.
# Manually set them here
set(PLATFORM_HEADERS
  ${BAKGE_SOURCE_DIR}/include/bakge/platform/${PLATFORM_PREFIX}_Bakge
  ${BAKGE_SOURCE_DIR}/include/bakge/system/Clock
  ${BAKGE_SOURCE_DIR}/include/bakge/core/Utility
  ${BAKGE_SOURCE_DIR}/include/bakge/mutex/${PLATFORM_PREFIX}_Mutex
  ${BAKGE_SOURCE_DIR}/include/bakge/thread/${PLATFORM_PREFIX}_Thread
  ${BAKGE_SOURCE_DIR}/include/bakge/socket/${PLATFORM_PREFIX}_Socket
  ${BAKGE_SOURCE_DIR}/include/bakge/packet/${PLATFORM_PREFIX}_Packet
)

add_library(bakge ${MODULES} ${PLATFORM_MODULES} ${HEADERS}
                                        ${PLATFORM_HEADERS})
if(BUILD_SHARED_LIBS)
  target_link_libraries(bakge ${BAKGE_LIBRARIES})
endif()

