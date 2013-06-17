
cmake_minimum_required (VERSION 2.6)

set(EXECUTABLE_OUTPUT_PATH ${BAKGE_SDK_EXAMPLES_OUTPUT_PATH})

set(BAKGE_EXAMPLE_SUITE
  ${BAKGE_SOURCE_DIR}/example/SimpleEngine
)

foreach(example ${BAKGE_EXAMPLE_SUITE})
  add_subdirectory(${example})
endforeach(example)
