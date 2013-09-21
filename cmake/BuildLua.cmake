

if(LUA_TARGET)

  include_directories(${LUA_TARGET}/src)

  set(LUA_SOURCES
    ${LUA_TARGET}/src/lapi.c
    ${LUA_TARGET}/src/lcode.c
    ${LUA_TARGET}/src/ldebug.c
    ${LUA_TARGET}/src/ldo.c
    ${LUA_TARGET}/src/ldump.c
    ${LUA_TARGET}/src/lfunc.c
    ${LUA_TARGET}/src/lgc.c
    ${LUA_TARGET}/src/llex.c
    ${LUA_TARGET}/src/lmem.c
    ${LUA_TARGET}/src/lobject.c
    ${LUA_TARGET}/src/lopcodes.c
    ${LUA_TARGET}/src/lparser.c
    ${LUA_TARGET}/src/lstate.c
    ${LUA_TARGET}/src/lstring.c
    ${LUA_TARGET}/src/ltable.c
    ${LUA_TARGET}/src/ltm.c
    ${LUA_TARGET}/src/lundump.c
    ${LUA_TARGET}/src/lvm.c
    ${LUA_TARGET}/src/lzio.c
    ${LUA_TARGET}/src/lauxlib.c
    ${LUA_TARGET}/src/lbaselib.c
    ${LUA_TARGET}/src/ldblib.c
    ${LUA_TARGET}/src/liolib.c
    ${LUA_TARGET}/src/lmathlib.c
    ${LUA_TARGET}/src/loslib.c
    ${LUA_TARGET}/src/ltablib.c
    ${LUA_TARGET}/src/lstrlib.c
    ${LUA_TARGET}/src/loadlib.c
    ${LUA_TARGET}/src/linit.c
  )
  
  set(LUA_HEADERS
    ${LUA_TARGET}/src/lua.h
    ${LUA_TARGET}/src/lualib.h
    ${LUA_TARGET}/src/luaconf.h
    ${LUA_TARGET}/src/lauxlib.h
  )
  
  if(WIN32)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
  endif()
  
  if(BUILD_SHARED_LIBS)
    if(WIN32)
      add_definitions(-DLUA_BUILD_AS_DLL)
    else()
      set(LUA_LIBRARY_TYPE SHARED)
    endif()
  endif()

  add_library(${BAKGE_LUA_TARGET} ${LUA_LIBRARY_TYPE} ${LUA_SOURCES})

  # Lua needs some other shared libraries
  if(BUILD_SHARED_LIBS AND UNIX)
    target_link_libraries(${BAKGE_LUA_TARGET} m)
  endif()

else()
  message("Couldn't find Lua path")
endif()

