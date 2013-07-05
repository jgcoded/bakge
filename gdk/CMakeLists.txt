# Bakge GDK CMake file

cmake_minimum_required (VERSION 2.6)

option(BAKGE_GDK_BUILD_ENGINE "Build the official Bakge engine application" ON)

if(BAKGE_GDK_BUILD_ENGINE)
  add_subdirectory(engine)
endif()
