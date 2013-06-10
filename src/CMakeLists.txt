# Bakge CMake file

cmake_minimum_required (VERSION 2.6)

include_directories(${BAKGE_SOURCE_DIR}/include)

set(MODULES
  core/Bindable.cpp
  core/Drawable.cpp
  core/Engine.cpp
  core/EventHandler.cpp
  core/Renderer.cpp
  core/Texture.cpp
  core/Window.cpp
)

add_library(BAKGE OBJECT ${MODULES})

