cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(LIBJSON)
add_definitions(-D_UNICODE -D_CRT_SECURE_NO_WARNINGS -D_SCL_SECURE_NO_WARNINGS)
SET(SRC_LIST
	src/json_reader.cpp
	src/json_tool.h
	src/json_value.cpp
	src/json_valueiterator.inl
	src/json_writer.cpp
	include/json/allocator.h
	include/json/assertions.h
	include/json/autolink.h
	include/json/config.h
	include/json/features.h
	include/json/forwards.h
	include/json/reader.h
	include/json/value.h
	include/json/version.h
	include/json/writer.h
	)

ADD_EXECUTABLE(format ${SRC_LIST})