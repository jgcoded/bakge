

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

  if(BUILD_SHARED_LIBS)
    if(WIN32)
      add_definitions(-DENET_DLL)
    else()
      set(ENET_LIBRARY_TYPE SHARED)
    endif()
  endif()

  add_library(${BAKGE_ENET_TARGET} ${ENET_LIBRARY_TYPE} ${ENET_SOURCES})

  if(WIN32)
    target_link_libraries(${BAKGE_ENET_TARGET} ws2_32 winmm)
  endif()

else()
  message("Couldn't find Enet path")
endif()
