file(GLOB SDL2_INCLUDE_FILES SDL2/*.h)

# Make the files visible on qtcreator
add_custom_target(SDL2_INCLUDES ALL SOURCES ${SDL2_INCLUDE_FILES})

