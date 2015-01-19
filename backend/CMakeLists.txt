include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set(
    Sdltemplatebackend_SRCS
    modules/Sdltemplate/backend.cpp
    modules/Sdltemplate/mytype.cpp
)

add_library(Sdltemplatebackend MODULE
    ${Sdltemplatebackend_SRCS}
)

set_target_properties(Sdltemplatebackend PROPERTIES
         LIBRARY_OUTPUT_DIRECTORY Sdltemplate)

qt5_use_modules(Sdltemplatebackend Gui Qml Quick)

# Copy qmldir file to build dir for running in QtCreator
add_custom_target(Sdltemplatebackend-qmldir ALL
    COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/modules/Sdltemplate/qmldir ${CMAKE_CURRENT_BINARY_DIR}/Sdltemplate
    DEPENDS ${QMLFILES}
)

# Install plugin file
install(TARGETS Sdltemplatebackend DESTINATION ${QT_IMPORTS_DIR}/Sdltemplate/)
install(FILES   modules/Sdltemplate/qmldir DESTINATION ${QT_IMPORTS_DIR}/Sdltemplate/)

