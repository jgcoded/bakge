# Bakge CMake file

cmake_minimum_required (VERSION 2.6)

include_directories(${BAKGE_SOURCE_DIR}/include)

set(MODULES
  api/Window
  core/Bindable
  core/Drawable
  core/Engine
  core/EventHandler
  core/Renderer
  core/Utility
  graphics/Texture
  renderer/FrontRenderer
)

set(PLATFORM_MODULES
  window
)

if(WIN32)
  set(PLATFORM_PREFIX "win32")
endif(WIN32)

add_library(bakge ${MODULES}.cpp ${PLATFORM_MODULES}/${PLATFORM_PREFIX}*)