project(ubuntu-touch-sdl-template C CXX)
cmake_minimum_required(VERSION 2.8.9)

# Do not remove this line, its required for the correct functionality of the Ubuntu-SDK
set(UBUNTU_MANIFEST_PATH "manifest.json.in" CACHE INTERNAL "Tells QtCreator location and name of the manifest file")
set (CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(Qt5Core)
find_package(Qt5Qml)
find_package(Qt5Quick)
# find_package(ubuntu-sdk-libs)

# Automatically create moc files
set(CMAKE_AUTOMOC ON)

# Components PATH
execute_process(
    COMMAND dpkg-architecture -qDEB_HOST_MULTIARCH
    OUTPUT_VARIABLE ARCH_TRIPLET
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

set(QT_IMPORTS_DIR "lib/${ARCH_TRIPLET}")

option(INSTALL_TESTS "Install the tests on make install" on)

set(APP_NAME          ubuntu-touch-sdl-template)
set(UBUNTU-TOUCH-SDL-TEMPLATE_DIR "share/qml/ubuntu-touch-sdl-template")
set(MAIN_QML          "ubuntu-touch-sdl-template.qml")
set(ICON              "graphics/ubuntu-touch-sdl-template.png")

# Set install paths
set(CMAKE_INSTALL_PREFIX /)
set(DATA_DIR /)
set(DESKTOP_DIR ${DATA_DIR})
set(DESKTOP_FILE_NAME "sdltemplate.desktop")

set(EXEC "qmlscene $@ ${UBUNTU-TOUCH-SDL-TEMPLATE_DIR}/${MAIN_QML}")

# This command figures out the target architecture for use in the manifest file
execute_process(
  COMMAND dpkg-architecture -qDEB_HOST_ARCH
  OUTPUT_VARIABLE CLICK_ARCH
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

configure_file(manifest.json.in ${CMAKE_CURRENT_BINARY_DIR}/manifest.json)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/manifest.json
        DESTINATION ${CMAKE_INSTALL_PREFIX})

install(DIRECTORY "app/graphics" DESTINATION ${DATA_DIR})
install(FILES "sdltemplate.apparmor" DESTINATION ${DATA_DIR})

add_subdirectory(app)
add_subdirectory(backend)
add_subdirectory(po)

add_custom_target("autopilot" chmod +x ${CMAKE_SOURCE_DIR}/app/tests/autopilot/run
                    COMMAND ${CMAKE_SOURCE_DIR}/app/tests/autopilot/run
                    DEPENDS ubuntu-touch-sdl-templatebackend ubuntu-touch-sdl-templatebackend-qmldir
                    WORKING_DIRECTORY ./app)

add_custom_target("check" /usr/bin/qmltestrunner -input ${CMAKE_SOURCE_DIR}/app/tests/unit -import ${CMAKE_BINARY_DIR}/backend
                    DEPENDS ubuntu-touch-sdl-templatebackend ubuntu-touch-sdl-templatebackend-qmldir
                    WORKING_DIRECTORY ./app)

add_custom_target("run" /usr/bin/qmlscene -I ${CMAKE_BINARY_DIR}/backend  ${CMAKE_SOURCE_DIR}/app/ubuntu-touch-sdl-template.qml
                    DEPENDS ubuntu-touch-sdl-templatebackend ubuntu-touch-sdl-templatebackend-qmldir
                    WORKING_DIRECTORY ./app)

# No op custom target for all not compiled files, so they show up in the QtCreator project tree
add_custom_target("ubuntu-touch-sdl-template_ClickFiles" ALL SOURCES "sdltemplate.apparmor" "manifest.json.in")

