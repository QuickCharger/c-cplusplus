AUTO_FILES("." "src" "\\.(cc|cpp|h)$")

ADD_EXECUTABLE(Server "${src}")
target_link_libraries(Server ws2_32.lib)