
set(OPENAL_MIRROR http://connect.creativelabs.com/openal/Downloads/openal-soft-1.13.tbz2)
set(OPENAL_TARGET ${BAKGE_SOURCE_DIR}/lib/openal-1.13)
set(OPENAL_ARCHIVE ${OPENAL_TARGET}.tbz2)

if(NOT EXISTS ${OPENAL_ARCHIVE} AND NOT EXISTS ${OPENAL_TARGET})
  message("-- Downloading archive ${OPENAL_ARCHIVE}")
  file(DOWNLOAD ${OPENAL_MIRROR} ${OPENAL_ARCHIVE})
endif()

if(NOT EXISTS ${OPENAL_TARGET} AND EXISTS ${OPENAL_ARCHIVE})
  message("-- Unpacking archive ${OPENAL_ARCHIVE}")
  execute_process(COMMAND ${CMAKE_COMMAND} -E tar zxvf ${OPENAL_ARCHIVE} DEPENDS ${OPENAL_ARCHIVE} WORKING_DIRECTORY ${BAKGE_SOURCE_DIR}/lib OUTPUT_QUIET)
  message("-- Removing archive ${OPENAL_ARCHIVE}")
  file(REMOVE ${OPENAL_ARCHIVE})
  file(RENAME ${BAKGE_SOURCE_DIR}/lib/openal-soft-1.13 ${OPENAL_TARGET})
endif()

