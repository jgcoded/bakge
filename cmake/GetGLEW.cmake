
set(GLEW_MIRROR http://sourceforge.net/projects/glew/files/glew/1.9.0/glew-1.9.0.tgz/download?use_mirror=autoselect)
set(GLEW_TARGET ${BAKGE_SOURCE_DIR}/lib/glew-1.9.0)
set(GLEW_ARCHIVE ${GLEW_TARGET}.tar.gz)

if(NOT EXISTS ${GLEW_ARCHIVE} AND NOT EXISTS ${GLEW_TARGET})
  message(STATUS "GLEW library not found")
  message(STATUS "  Downloading archive ${GLEW_ARCHIVE}")
  file(DOWNLOAD ${GLEW_MIRROR} ${GLEW_ARCHIVE})
endif()

if(NOT EXISTS ${GLEW_TARGET} AND EXISTS ${GLEW_ARCHIVE})
  message(STATUS "  Unpacking archive ${GLEW_ARCHIVE}")
  execute_process(COMMAND ${CMAKE_COMMAND} -E tar zxvf ${GLEW_ARCHIVE} DEPENDS ${GLEW_ARCHIVE} WORKING_DIRECTORY ${BAKGE_SOURCE_DIR}/lib OUTPUT_QUIET)
  message(STATUS "  Removing archive ${GLEW_ARCHIVE}")
  file(REMOVE ${GLEW_ARCHIVE})
endif()

