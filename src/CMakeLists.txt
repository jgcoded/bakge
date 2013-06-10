# Bakge CMake file

cmake_minimum_required (VERSION 2.6)

include_directories(${BAKGE_SOURCE_DIR}/include)

set(MODULES
  core/Bindable
  core/Drawable
  core/Engine
  core/EventHandler
  core/Renderer
  core/Texture
  core/Utility
  core/Window
  renderer/FrontRenderer
)

add_library(bakge ${MODULES}.cpp)

