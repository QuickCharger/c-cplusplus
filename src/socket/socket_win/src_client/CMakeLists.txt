AUTO_FILES("." "src" "\\.(cc|cpp|h)$")

ADD_EXECUTABLE(Client "${src}")
target_link_libraries(Client ws2_32.lib)