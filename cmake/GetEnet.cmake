
set(ENET_MIRROR http://enet.bespin.org/download/enet-1.3.10.tar.gz)
set(ENET_TARGET ${BAKGE_SOURCE_DIR}/lib/enet-1.3.10)
set(ENET_ARCHIVE ${ENET_TARGET}.tar.gz)

if(NOT EXISTS ${ENET_ARCHIVE} AND NOT EXISTS ${ENET_TARGET})
  message(STATUS "Enet library not found")
  message(STATUS "  Downloading archive ${ENET_ARCHIVE}")
  file(DOWNLOAD ${ENET_MIRROR} ${ENET_ARCHIVE})
endif()

if(NOT EXISTS ${ENET_TARGET} AND EXISTS ${ENET_ARCHIVE})
  message(STATUS "  Unpacking ${ENET_ARCHIVE}")
  execute_process(COMMAND ${CMAKE_COMMAND} -E tar zxvf ${ENET_ARCHIVE} DEPENDS
${ENET_ARCHIVE} WORKING_DIRECTORY ${BAKGE_SOURCE_DIR}/lib OUTPUT_QUIET)
  message(STATUS "  Removing archive ${ENET_ARCHIVE}")
  file(REMOVE ${ENET_ARCHIVE})
endif()
