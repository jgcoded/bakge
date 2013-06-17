# Bakge unit tests CMake file

cmake_minimum_required(VERSION 2.6)

if(BAKGE_BUILD_SDK)
  set(TESTS_SUBDIR "test")
endif()

set(TESTS
  clock
  linkedlist
  loadfile
  matrix
  node
  pawn
  frontrenderer
  quaternion
  texture
  thread
  types
  vector4
  window
)

set(EXECUTABLE_OUTPUT_PATH ${BAKGE_SDK_TESTS_OUTPUT_PATH})

if(NOT APPLE)
  foreach(test ${TESTS})
    add_executable(${test} ${test}.cpp)
    target_link_libraries(${test} bakge ${BAKGE_LIBRARIES})
  endforeach(test)
else()
  foreach(test ${TESTS})
    add_executable(${test} MACOSX_BUNDLE ${test})
    target_link_libraries(${test} bakge ${BAKGE_LIBRARIES})
    set_target_properties(${test} PROPERTIES MACOSX_BUNDLE_BUNDLE_NAME ${test})
    set_target_properties(${test} PROPERTIES MACOSX_BUNDLE_SHORT_VERSION_STRING ${BAKGE_GLFW_VERSION}
                                             MACOSX_BUNDLE_LONG_VERSION_STRING ${BAKGE_GLFW_VERSION_FULL})
  endforeach(test)
endif()
