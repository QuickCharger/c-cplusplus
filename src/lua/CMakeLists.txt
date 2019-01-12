INCLUDE_DIRECTORIES(
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

LINK_DIRECTORIES(
	${CMAKE_CURRENT_SOURCE_DIR}/lib
)

ADD_EXECUTABLE(lua main.cpp test.lua)

target_link_libraries(lua lua.lib
)
