# Bakge CMake file

cmake_minimum_required (VERSION 2.6)


########################################
# COMMON HEADERS & MODULES
########################################

set(MODULES
  api/Mutex
  api/Thread
  audio/Environment
  audio/Source
  audio/Stream
  data/File
  core/Bindable
  core/Drawable
  core/Engine
  core/EventHandler
  core/Utility
  core/Window
  graphics/Camera
  graphics/Camera2D
  graphics/Camera3D
  graphics/Crowd
  graphics/Font
  graphics/Mesh
  graphics/Node
  graphics/Pawn
  graphics/Shader
  graphics/Shape
  graphics/Texture
  graphics/shapes/Cube
  graphics/shapes/Rectangle
  input/GamePad
  ui/Anchor
  ui/Clickable
  ui/Container
  ui/Draggable
  ui/Frame
  ui/Hoverable
  ui/Resizable
  math/Vector3
  math/Vector4
  math/Quaternion
  math/Matrix
  system/Device
)

# Create headers list, add those without a source file
# since they won't get picked up by the following foreach loop
set(HEADERS
  ${BAKGE_SOURCE_DIR}/include/bakge/Bakge
  ${BAKGE_SOURCE_DIR}/include/bakge/math/Math
  ${BAKGE_SOURCE_DIR}/include/bakge/core/Type
  ${BAKGE_SOURCE_DIR}/include/bakge/data/LinkedList
  ${BAKGE_SOURCE_DIR}/include/bakge/data/SingleNode
  ${BAKGE_SOURCE_DIR}/include/bakge/input/XboxController
)

foreach(module ${MODULES})
  list(APPEND HEADERS ${BAKGE_SOURCE_DIR}/include/bakge/${module})
endforeach(module)


########################################
# PLATFORM MODULES & HEADERS
########################################

if(UNIX AND NOT APPLE)
  set(PLATFORM_PREFIX "x11")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse -msse2 -march=native")
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
)

# Extern libraries in the source tree
set(EXTERN_SOURCES
  ${BAKGE_SOURCE_DIR}/extern/stb/stb_image.c
  ${BAKGE_SOURCE_DIR}/extern/stb/stb_truetype.c
  ${BAKGE_SOURCE_DIR}/extern/stb/stb_vorbis.c
)

set(OTHER_SOURCES
  internal/Debug
)

if(BUILD_SHARED_LIBS)
  # It's a matter of taste
  remove_definitions(-Dbakge_EXPORTS)
  add_definitions(-DBAKGE_EXPORTS)
endif()

add_definitions(-DSTB_TRUETYPE_IMPLEMENTATION)
add_library(bakge ${EXTERN_SOURCES} ${MODULES} ${PLATFORM_MODULES} ${HEADERS}
                                        ${PLATFORM_HEADERS} ${OTHER_SOURCES})
if(BUILD_SHARED_LIBS)
  target_link_libraries(bakge ${BAKGE_LIBRARIES})
  target_link_libraries(bakge ${BAKGE_BULLET_TARGETS})
endif()
