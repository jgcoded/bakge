
set(LUA_MIRROR http://www.lua.org/ftp/lua-5.1.5.tar.gz)
set(LUA_TARGET ${BAKGE_SOURCE_DIR}/lib/lua-5.1.5)
set(LUA_ARCHIVE ${LUA_TARGET}.tar.gz)

if(NOT EXISTS ${LUA_ARCHIVE} AND NOT EXISTS ${LUA_TARGET})
  message("-- Downloading archive ${LUA_ARCHIVE}")
  file(DOWNLOAD ${LUA_MIRROR} ${LUA_ARCHIVE})
endif()

if(NOT EXISTS ${LUA_TARGET} AND EXISTS ${LUA_ARCHIVE})
  message("-- Unpacking archive ${LUA_ARCHIVE}")
  execute_process(COMMAND ${CMAKE_COMMAND} -E tar zxvf ${LUA_ARCHIVE} DEPENDS ${LUA_ARCHIVE} WORKING_DIRECTORY ${BAKGE_SOURCE_DIR}/lib OUTPUT_QUIET)
  message("-- Removing archive ${LUA_ARCHIVE}")
  file(REMOVE ${LUA_ARCHIVE})
endif()

