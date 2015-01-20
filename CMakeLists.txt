project(ubuntu-touch-sdl-template C CXX)
cmake_minimum_required(VERSION 2.8.9)

# Do not remove this line, its required for the correct functionality of the Ubuntu-SDK
set(UBUNTU_MANIFEST_PATH "manifest.json.in" CACHE INTERNAL "Tells QtCreator location and name of the manifest file")
set (CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Automatically create moc files
set(CMAKE_AUTOMOC ON)

set(APP_NAME          ubuntu-touch-sdl-template)
set(MAIN              ${APP_NAME})
set(ICON              "ubuntu-touch-sdl-template.png")

# Set install paths
set(CMAKE_INSTALL_PREFIX /)
set(DATA_DIR /)
set(DESKTOP_DIR ${DATA_DIR})
set(DESKTOP_FILE_NAME "ubuntu-touch-sdl-template.desktop")

set(EXEC "${APP_NAME}")

# This command figures out the target architecture for use in the manifest file
execute_process(
  COMMAND dpkg-architecture -qDEB_HOST_ARCH
  OUTPUT_VARIABLE CLICK_ARCH
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

configure_file(manifest.json.in ${CMAKE_CURRENT_BINARY_DIR}/manifest.json)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/manifest.json
        DESTINATION ${CMAKE_INSTALL_PREFIX})
install(FILES ${DESKTOP_FILE_NAME}
        DESTINATION ${CMAKE_INSTALL_PREFIX})

install(FILES ${ICON} DESTINATION ${DATA_DIR})
install(FILES "ubuntu-touch-sdl-template.apparmor" DESTINATION ${DATA_DIR})

# Add source files from src/
set(
    EXEC_SOURCES
    src/main.c
)

# Add and install binary
add_executable(${EXEC} ${EXEC_SOURCES}) 
install_targets(${CMAKE_INSTALL_PREFIX} ${EXEC})

# Add the path to our local libraries
set(LIBRARY_SEARCH_PATHS "lib/${CLICK_ARCH}/")

# Find libSDL2 (system-wide or local installation)
find_library(SDL2_LIB NAMES SDL2 PATHS ${LIBRARY_SEARCH_PATHS})

# Find libasound (system-wide or local installation)
find_library(ASOUND_LIB NAMES asound PATHS ${LIBRARY_SEARCH_PATHS})

# Find pulseaudio libraries (system-wide or local installation)
find_library(PULSE_LIB NAMES pulse PATHS ${LIBRARY_SEARCH_PATHS})
find_library(PULSE_LIB_SIMPLE NAMES pulse-simple PATHS ${LIBRARY_SEARCH_PATHS})

# Find X11 libraries (system-wide or local installation)
find_library(XCURSOR_LIB NAMES Xcursor PATHS ${LIBRARY_SEARCH_PATHS})
find_library(XINERAMA_LIB NAMES Xinerama PATHS ${LIBRARY_SEARCH_PATHS})
find_library(XKBCOMMON_LIB NAMES xkbcommon PATHS ${LIBRARY_SEARCH_PATHS})
find_library(XI_LIB NAMES Xi PATHS ${LIBRARY_SEARCH_PATHS})
find_library(XRANDR_LIB NAMES Xrandr PATHS ${LIBRARY_SEARCH_PATHS})
find_library(XSS_LIB NAMES Xss PATHS ${LIBRARY_SEARCH_PATHS})

# List of libraries
set(
    EXEC_LIBS
    ${SDL2_LIB}
    ${ASOUND_LIB}
    ${PULSE_LIB}
    ${PULSE_LIB_SIMPLE}
    X11
    Xext
    Xxf86vm
    ${XCURSOR_LIB}
    ${XINERAMA_LIB}
    ${XKBCOMMON_LIB}
    ${XI_LIB}
    ${XRANDR_LIB}
    ${XSS_LIB}
    wayland-client
    wayland-cursor
    wayland-egl
    dl
    m
    pthread)

# Link against libSDL2
target_link_libraries(${EXEC} ${EXEC_LIBS})

# Include headers
add_subdirectory(include)

# Include dynamic libraries
add_subdirectory(lib)

# Install run.sh
install_programs(${CMAKE_INSTALL_PREFIX} run.sh)

add_custom_target("check" ${EXEC}
                    DEPENDS ${EXEC}
                    WORKING_DIRECTORY .)

add_custom_target("run" run.sh
                    DEPENDS ${EXEC}
                    WORKING_DIRECTORY .)

# No op custom target for all not compiled files, so they show up in the QtCreator project tree
add_custom_target("ubuntu-touch-sdl-template_ClickFiles" ALL SOURCES ${DESKTOP_FILE_NAME} "ubuntu-touch-sdl-template.apparmor" "manifest.json.in" "run.sh")
