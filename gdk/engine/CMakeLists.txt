# Bakge Official engine CMake file

cmake_minimum_required (VERSION 2.6)

set(BAKGE_GDK_ENGINE_DIR ${CMAKE_SOURCE_DIR}/gdk/engine)

include_directories(${BAKGE_GDK_ENGINE_DIR}/include)

set(BAKGE_GDK_ENGINE_HEADERS
  ${BAKGE_GDK_ENGINE_DIR}/include/bakge/gdk/GameEngine
)

set(BAKGE_GDK_ENGINE_SOURCES
  ${BAKGE_GDK_ENGINE_DIR}/src/main
  ${BAKGE_GDK_ENGINE_DIR}/src/GameEngine
)

if(UNIX AND NOT APPLE)
  set(LIB_GLOB *.so*)
endif()

if(WIN32)
  set(LIB_GLOB *.dll)
endif()

if(UNIX AND APPLE)
  set(LIB_GLOB *.dylib*)
endif()

file(GLOB BAKGE_GDK_COPY_LIBS ${BAKGE_SDK_BIN_PATH}/${LIB_GLOB})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BAKGE_GDK_ENGINE_DIR}/bin/${CMAKE_BUILD_TYPE})

foreach(COPYLIB ${BAKGE_GDK_COPY_LIBS})
  add_custom_command(TARGET ${CMAKE_BUILD_TYPE} POST_BUILD COMMAND
        ${CMAKE_COMMAND} -E copy ${COPYLIB} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endforeach()

add_executable(Bakge ${BAKGE_GDK_ENGINE_HEADERS} ${BAKGE_GDK_ENGINE_SOURCES}.cpp)
target_link_libraries(Bakge bakge ${BAKGE_LIBRARIES})
