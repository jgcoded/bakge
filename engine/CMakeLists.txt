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


set(BAKGE_TARGETS lua bakge ${BAKGE_GLFW_LIB} glew)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BAKGE_GDK_DIR}/${CMAKE_BUILD_TYPE})

add_executable(Bakge ${BAKGE_GDK_ENGINE_HEADERS} ${BAKGE_GDK_ENGINE_SOURCES}.cpp)
target_link_libraries(Bakge bakge ${BAKGE_LIBRARIES})

add_custom_target(GDKEngineCopyLibs)
foreach(COPYLIB ${BAKGE_TARGETS})
  add_custom_command(TARGET GDKEngineCopyLibs POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${COPYLIB}>
        ${BAKGE_GDK_DIR}/${CMAKE_BUILD_TYPE})
endforeach()

add_dependencies(GDKEngineCopyLibs ${BAKGE_TARGETS})
add_dependencies(Bakge GDKEngineCopyLibs)
