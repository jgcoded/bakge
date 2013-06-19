
if(GLEW_TARGET)

  set(GLEW_SOURCES
    ${GLEW_TARGET}/src/glew
    ${GLEW_TARGET}/src/glewinfo
    ${GLEW_TARGET}/src/visualinfo
  )

  add_library(glew ${GLEW_SOURCES})

else()
  message("Couldn't find GLEW path")
endif()

