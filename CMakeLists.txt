# Bakge CMake file

cmake_minimum_required (VERSION 2.6)

project (BAKGE)

include_directories(${BAKGE_SOURCE_DIR}/include)

set(MODULES
  core/Window
  core/Texture
  core/Engine
  core/Renderer
  core/Bindable
  core/Drawable
)

foreach(module ${MODULES})
  add_library(obj/${module} OBJECT
              src/${module}.cpp)
endforeach(module)

add_subdirectory(test)
