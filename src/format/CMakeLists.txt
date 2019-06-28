cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(Format)

SET(JSON_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../lib_json/)

INCLUDE_DIRECTORIES(
	${JSON_PATH}
	${JSON_PATH}/include
	${JSON_PATH}/src
)

add_definitions(-D_UNICODE -D_CRT_SECURE_NO_WARNINGS -D_SCL_SECURE_NO_WARNINGS)

SET(SRC_LIST
	main.cpp
	func.h

	${JSON_PATH}/include/json/allocator.h
	${JSON_PATH}/include/json/assertions.h
	${JSON_PATH}/include/json/autolink.h
	${JSON_PATH}/include/json/config.h
	${JSON_PATH}/include/json/features.h
	${JSON_PATH}/include/json/forwards.h
	${JSON_PATH}/include/json/reader.h
	${JSON_PATH}/include/json/value.h
	${JSON_PATH}/include/json/version.h
	${JSON_PATH}/include/json/writer.h
	${JSON_PATH}/src/json_reader.cpp
	${JSON_PATH}/src/json_tool.h
	${JSON_PATH}/src/json_value.cpp
	${JSON_PATH}/src/json_valueiterator.inl
	${JSON_PATH}/src/json_writer.cpp
	)

ADD_EXECUTABLE(format ${SRC_LIST})