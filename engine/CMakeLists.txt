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

# So Bakge engine executable can find shared libs in its directory
# Without this dynamic linking won't work on Linux
link_directories(${BAKGE_GDK_DIR}/${CMAKE_BUILD_TYPE})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BAKGE_GDK_DIR}/${CMAKE_BUILD_TYPE})
add_executable(Bakge ${BAKGE_GDK_ENGINE_HEADERS} ${BAKGE_GDK_ENGINE_SOURCES})
target_link_libraries(Bakge bakge ${BAKGE_LIBRARIES})

# Copy libraries over to GDK directory
add_custom_target(GDKEngineCopyLibs)

foreach(COPYLIB ${BAKGE_TARGETS_LIST})
  add_custom_command(TARGET GDKEngineCopyLibs POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${COPYLIB}>
        ${BAKGE_GDK_DIR}/${CMAKE_BUILD_TYPE})

  # If we're on Linux there may be other generated files
  if(UNIX AND NOT APPLE)
    add_custom_command(TARGET GDKEngineCopyLibs POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_LINKER_FILE:${COPYLIB}>
        ${BAKGE_GDK_DIR}/${CMAKE_BUILD_TYPE})
    add_custom_command(TARGET GDKEngineCopyLibs POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_SONAME_FILE:${COPYLIB}>
        ${BAKGE_GDK_DIR}/${CMAKE_BUILD_TYPE})
  endif()
endforeach()

add_dependencies(GDKEngineCopyLibs ${BAKGE_TARGETS_LIST})
add_dependencies(Bakge GDKEngineCopyLibs)

