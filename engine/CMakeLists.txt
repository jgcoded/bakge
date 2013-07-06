# Bakge Official engine CMake file

cmake_minimum_required (VERSION 2.6)

set(BAKGE_GDK_DIR ${CMAKE_SOURCE_DIR}/gdk)
set(BAKGE_GDK_ENGINE_DIR ${CMAKE_SOURCE_DIR}/engine)

include_directories(${BAKGE_GDK_ENGINE_DIR}/include)

set(BAKGE_GDK_ENGINE_HEADERS
  ${BAKGE_SOURCE_DIR}/engine/include/bakge/gdk/engine/GDKEngine
  ${BAKGE_SOURCE_DIR}/engine/include/bakge/gdk/engine/GameEngine
)

set(BAKGE_GDK_ENGINE_SOURCES
  ${BAKGE_SOURCE_DIR}/engine/src/gdk/engine/GDKEngine
  ${BAKGE_SOURCE_DIR}/engine/src/gdk/engine/GameEngine
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

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BAKGE_GDK_DIR}/${CMAKE_BUILD_TYPE})

add_executable(Bakge ${BAKGE_GDK_ENGINE_HEADERS} ${BAKGE_GDK_ENGINE_SOURCES}.cpp)
target_link_libraries(Bakge bakge ${BAKGE_LIBRARIES})

foreach(COPYLIB ${BAKGE_GDK_COPY_LIBS})
  add_custom_command(TARGET Bakge POST_BUILD COMMAND
    ${CMAKE_COMMAND} -E copy ${COPYLIB} ${BAKGE_GDK_DIR}/${CMAKE_BUILD_TYPE})
endforeach()
