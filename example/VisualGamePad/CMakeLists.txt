# Bakge example VisualGamePad program

cmake_minimum_required (VERSION 2.6)

set(BAKGE_EXAMPLE_VISUALGAMEPAD_SOURCES
  ${BAKGE_SOURCE_DIR}/example/VisualGamePad/VisualGamePad
  ${BAKGE_SOURCE_DIR}/example/VisualGamePad/main
)

add_executable(VisualGamePad ${BAKGE_EXAMPLE_VISUALGAMEPAD_SOURCES})
target_link_libraries(VisualGamePad bakge ${BAKGE_LIBRARIES})
