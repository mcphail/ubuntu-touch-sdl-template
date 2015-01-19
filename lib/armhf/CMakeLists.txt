file(GLOB ARMHF_LIB_FILES *.so *.so.*)

# Make the files visible on qtcreator
add_custom_target(ARMHF_LIBS ALL SOURCES ${ARMHF_LIB_FILES})

install(FILES ${ARMHF_LIB_FILES} DESTINATION ${CMAKE_INSTALL_PREFIX}lib/armhf)
