

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

  set(ENET_HEADERS
    ${ENET_TARGET}/include/enet/callbacks.h
    ${ENET_TARGET}/include/enet/enet.h
    ${ENET_TARGET}/include/enet/list.h
    ${ENET_TARGET}/include/enet/protocol.h
    ${ENET_TARGET}/include/enet/time.h
    ${ENET_TARGET}/include/enet/types.h
    ${ENET_TARGET}/include/enet/unix.h
    ${ENET_TARGET}/include/enet/utility.h
    ${ENET_TARGET}/include/enet/win32.h
  )

else()
  message("Couldn't find Enet path")
endif()
