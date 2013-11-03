

if(ENET_TARGET)

  include_directories(${ENET_TARGET})

  set(ENET_SOURCES
    ${ENET_TARGET}/callbacks.c
    ${ENET_TARGET}/compress.c
    ${ENET_TARGET}/host.c
    ${ENET_TARGET}/list.c
    ${ENET_TARGET}/packet.c
    ${ENET_TARGET}/peer.c
    ${ENET_TARGET}/protocol.c
    ${ENET_TARGET}/unix.c 
    ${ENET_TARGET}/win32.c
  )

else()
  message("Couldn't find Enet path")
endif()
