# Bakge CMake file

cmake_minimum_required (VERSION 2.6)

include_directories(${BAKGE_SOURCE_DIR}/include)

set(MODULES
  core/Window.cpp
  core/Texture.cpp
  core/Engine.cpp
  core/Renderer.cpp
  core/Bindable.cpp
  core/Drawable.cpp
)

add_library(BAKGE OBJECT ${MODULES})

