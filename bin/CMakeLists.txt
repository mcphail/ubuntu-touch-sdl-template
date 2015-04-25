file(GLOB SHELL_FILES *.sh)

# Make the files visible on qtcreator
#add_custom_target(runsh)
#add_custom_command(TARGET runsh PRE_BUILD
#    COMMAND ${CMAKE_COMMAND} -E
#    copy run.sh ${CMAKE_INSTALL_PREFIX}bin/)

add_custom_target(SHELL_SCRIPTS ALL SOURCES ${SHELL_FILES})
install(PROGRAMS run.sh DESTINATION ${CMAKE_INSTALL_PREFIX}bin/)
