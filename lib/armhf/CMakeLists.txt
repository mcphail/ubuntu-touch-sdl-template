file(GLOB ARMHF_SO_FILES *.so *.so.*)
file(GLOB ARMHF_A_FILES *.a)

# Make the files visible on qtcreator
add_custom_target(ARMHF_SO_LIBS ALL SOURCES ${ARMHF_SO_FILES})
add_custom_target(ARMHF_A_LIBS ALL SOURCES ${ARMHF_A_FILES})

install(FILES ${ARMHF_SO_FILES} DESTINATION ${CMAKE_INSTALL_PREFIX}lib/armhf)
