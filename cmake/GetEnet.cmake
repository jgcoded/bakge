
set(ENET_MIRROR http://enet.bespin.org/download/enet-1.3.10.tar.gz)
set(ENET_TARGET ${BAKGE_SOURCE_DIR}/lib/enet-1.3.10)
set(ENET_ARCHIVE ${ENET_TARGET}.tar.gz)

if(NOT EXISTS ${ENET_ARCHIVE} AND NOT EXISTS ${ENET_TARGET})
  message(STATUS "Enet library not found")
  message(STATUS "  Downloading archive ${ENET_ARCHIVE}")
  file(DOWNLOAD ${ENET_MIRROR} ${ENET_ARCHIVE})
endif()