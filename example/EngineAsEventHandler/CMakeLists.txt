# Bakge example EngineAsEventHandler program

cmake_minimum_required (VERSION 2.6)

set(BAKGE_EXAMPLE_ENGINEASEVENTHANDLER_SOURCES
  ${BAKGE_SOURCE_DIR}/example/EngineAsEventHandler/EngineAsEventHandler
  ${BAKGE_SOURCE_DIR}/example/EngineAsEventHandler/main
)

add_executable(EngineAsEventHandler
  ${BAKGE_EXAMPLE_ENGINEASEVENTHANDLER_SOURCES}
)

target_link_libraries(EngineAsEventHandler
  bakge
  ${BAKGE_LIBRARIES}
)

