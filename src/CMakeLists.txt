# Bakge CMake file

cmake_minimum_required (VERSION 2.6)

include_directories(${BAKGE_SOURCE_DIR}/include)

set(MODULES
  api/Window
  api/Thread
  data/SingleNode
  data/LinkedList
  core/Bindable
  core/Drawable
  core/Engine
  core/Event
  core/EventHandler
  core/Renderer
  core/Utility
  graphics/Mesh
  graphics/Node
  graphics/Pawn
  graphics/Shader
  graphics/Shape
  graphics/Texture
  math/Vector4
  math/Quaternion
  math/Matrix
  renderer/FrontRenderer
)

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
  thread/${PLATFORM_PREFIX}_Thread
  utility/${PLATFORM_PREFIX}_Utility
  window/${PLATFORM_PREFIX}_Window
)

add_library(bakge ${MODULES} ${PLATFORM_MODULES})

