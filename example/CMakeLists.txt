
cmake_minimum_required (VERSION 2.6)

set(EXECUTABLE_OUTPUT_PATH ${BAKGE_SDK_EXAMPLES_OUTPUT_PATH})

set(BAKGE_EXAMPLE_SUITE
  ${BAKGE_SOURCE_DIR}/example/SimpleEngine
)

if(UNIX AND APPLE)
  list(APPEND CMAKE_CXX_FLAGS -ObjC++)
endif()

foreach(example ${BAKGE_EXAMPLE_SUITE})
  add_subdirectory(${example})
endforeach(example)

