# Bakge unit tests CMake file

cmake_minimum_required(VERSION 2.6)

project(BAKGE_TESTS)

include_directories(${BAKGE_TESTS_SOURCE_DIR}/../include)
link_directories(${BAKGE_TESTS_SOURCE_DIR}/../lib)

set(TESTS window types texture)
set(CORELIBS ${GLU_LIBRARY} ${OPENGL_LIBRARY} m /usr/local/lib/libglfw.a libbakge.a)

foreach(test ${TESTS})
  add_executable(${test} src/${test}.cpp)
  target_link_libraries(${test} ${CORELIBS})
endforeach(test)

