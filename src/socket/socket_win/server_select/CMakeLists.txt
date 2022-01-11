AUTO_FILES("." "src" "\\.(cc|cpp|h)$")

ADD_EXECUTABLE(ServerSelect "${src}")
target_link_libraries(ServerSelect ws2_32.lib)