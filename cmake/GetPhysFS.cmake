
set(PHYSFS_MIRROR http://icculus.org/physfs/downloads/physfs-2.0.3.tar.bz2)
set(PHYSFS_TARGET ${BAKGE_SOURCE_DIR}/lib/physfs-2.0.3)
set(PHYSFS_ARCHIVE ${PHYSFS_TARGET}.tar.bz2)

if(NOT EXISTS ${PHYSFS_ARCHIVE} AND NOT EXISTS ${PHYSFS_TARGET})
  message("-- Downloading archive ${PHYSFS_ARCHIVE}")
  file(DOWNLOAD ${PHYSFS_MIRROR} ${PHYSFS_ARCHIVE})
endif()

if(NOT EXISTS ${PHYSFS_TARGET} AND EXISTS ${PHYSFS_ARCHIVE})
  message("-- Unpacking archive ${PHYSFS_ARCHIVE}")
  execute_process(COMMAND ${CMAKE_COMMAND} -E tar zxvf ${PHYSFS_ARCHIVE} DEPENDS ${PHYSFS_ARCHIVE} WORKING_DIRECTORY ${BAKGE_SOURCE_DIR}/lib OUTPUT_QUIET)
  message("-- Removing archive ${PHYSFS_ARCHIVE}")
  file(REMOVE ${PHYSFS_ARCHIVE})
endif()

