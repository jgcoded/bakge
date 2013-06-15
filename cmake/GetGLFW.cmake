
set(GLFW_MIRROR http://sourceforge.net/projects/glfw/files/glfw/3.0/glfw-3.0.zip/download?use_mirror=autoselect)
set(GLFW_TARGET ${BAKGE_SOURCE_DIR}/lib/glfw-3.0)
set(GLFW_ARCHIVE ${GLFW_TARGET}.zip)

if(NOT EXISTS ${GLFW_ARCHIVE} AND NOT EXISTS ${GLFW_TARGET})
  message("-- Downloading archive ${GLFW_ARCHIVE}")
  file(DOWNLOAD ${GLFW_MIRROR} ${GLFW_ARCHIVE})
endif()

if(NOT EXISTS ${GLFW_TARGET} AND EXISTS ${GLFW_ARCHIVE})
  message("-- Unpacking archive ${GLFW_ARCHIVE}")
  execute_process(COMMAND ${CMAKE_COMMAND} -E tar xvf ${GLFW_ARCHIVE} DEPENDS ${GLFW_ARCHIVE} WORKING_DIRECTORY ${BAKGE_SOURCE_DIR}/lib OUTPUT_QUIET)
  message("-- Removing archive ${GLFW_ARCHIVE}")
  file(REMOVE ${GLFW_ARCHIVE})
endif()

