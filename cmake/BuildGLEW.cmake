
if(GLEW_TARGET)

  set(GLEW_SOURCES
    ${GLEW_TARGET}/src/glew
  )

  if(BUILD_SHARED_LIBS)
    add_definitions(-DGLEW_BUILD)
  else()
    add_definitions(-DGLEW_STATIC)
  endif()

  add_library(glew ${GLEW_SOURCES})

  if(BUILD_SHARED_LIBS)
    target_link_libraries(glew ${OPENGL_LIBRARY})
  endif()
  

else()
  message("Couldn't find GLEW path")
endif()

