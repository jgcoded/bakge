# Bakge example SimpleEngine program

cmake_minimum_required (VERSION 2.6)

set(BAKGE_EXAMPLE_SIMPLEENGINE_SOURCES
  ${BAKGE_SOURCE_DIR}/example/SimpleEngine/SimpleEngine
  ${BAKGE_SOURCE_DIR}/example/SimpleEngine/main
)

add_executable(SimpleEngine ${BAKGE_EXAMPLE_SIMPLEENGINE_SOURCES})
target_link_libraries(SimpleEngine bakge ${BAKGE_LIBRARIES})
