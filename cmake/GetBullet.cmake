
set(BULLET_MIRROR https://bullet.googlecode.com/files/bullet-2.81-rev2613.zip)
set(BULLET_TARGET ${BAKGE_SOURCE_DIR}/lib/bullet-2.81-rev2613)
set(BULLET_ARCHIVE ${BULLET_TARGET}.zip)

if(NOT EXISTS ${BULLET_ARCHIVE} AND NOT EXISTS ${BULLET_TARGET})
  message(STATUS "Bullet library not found")
  message(STATUS "  Downloading archive ${BULLET_ARCHIVE}")
  file(DOWNLOAD ${BULLET_MIRROR} ${BULLET_ARCHIVE})
endif()

if(NOT EXISTS ${BULLET_TARGET} AND EXISTS ${BULLET_ARCHIVE})
  message(STATUS "  Unpacking archive ${BULLET_ARCHIVE}")
  execute_process(COMMAND ${CMAKE_COMMAND} -E tar zxvf ${BULLET_ARCHIVE} DEPENDS ${BULLET_ARCHIVE} WORKING_DIRECTORY ${BAKGE_SOURCE_DIR}/lib OUTPUT_QUIET)
  message(STATUS "  Removing archive ${BULLET_ARCHIVE}")
  file(REMOVE ${BULLET_ARCHIVE})
endif()
