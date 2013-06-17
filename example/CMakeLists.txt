
cmake_minimum_required (VERSION 2.6)

set(BAKGE_EXAMPLE_SUITE
  ${BAKGE_SOURCE_DIR}/example/SimpleEngine
)

foreach(example ${BAKGE_EXAMPLE_SUITE})
  add_subdirectory(${example})
endforeach(example)
