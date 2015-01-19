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

# Link against libSDL
set(SDL2_SEARCH_PATHS lib/armhf)
find_library(SDL2_LIB NAMES SDL2 PATHS ${SDL2_SEARCH_PATHS})
target_link_libraries(${EXEC} ${SDL2_LIB})

# Include headers
add_subdirectory(include)

# Include dynamic libraries
add_subdirectory(lib)

# Install run.sh
install_programs(${CMAKE_INSTALL_PREFIX} run.sh)

add_custom_target("check" ${EXEC}
                    DEPENDS ${EXEC}
                    WORKING_DIRECTORY .)

add_custom_target("run" ${EXEC}
                    DEPENDS ${EXEC}
                    WORKING_DIRECTORY .)

# No op custom target for all not compiled files, so they show up in the QtCreator project tree
add_custom_target("ubuntu-touch-sdl-template_ClickFiles" ALL SOURCES ${DESKTOP_FILE_NAME} "ubuntu-touch-sdl-template.apparmor" "manifest.json.in" "run.sh")
