file(GLOB QML_JS_FILES *.qml *.js)

# Make the files visible on qtcreator
add_custom_target(ubuntu-touch-sdl-template_QMlFiles ALL SOURCES ${QML_JS_FILES})

# Substitute variables in the desktop file
configure_file(${DESKTOP_FILE_NAME}.in ${CMAKE_CURRENT_BINARY_DIR}/${DESKTOP_FILE_NAME}.in)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${DESKTOP_FILE_NAME} DESTINATION ${DESKTOP_DIR})
install(FILES ${QML_JS_FILES} DESTINATION ${UBUNTU-TOUCH-SDL-TEMPLATE_DIR})

add_subdirectory(components)
add_subdirectory(ui)

