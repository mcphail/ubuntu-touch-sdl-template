file(GLOB UI_QML_JS_FILES *.qml *.js)

# Make the files visible in the qtcreator tree
add_custom_target(ubuntu-touch-sdl-template_ui_QMlFiles ALL SOURCES ${UI_QML_JS_FILES})

install(FILES ${UI_QML_JS_FILES} DESTINATION ${UBUNTU-TOUCH-SDL-TEMPLATE_DIR}/ui)

