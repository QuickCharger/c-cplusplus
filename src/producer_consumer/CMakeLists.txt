cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(producer_consumer)

add_definitions(-D_UNICODE -D_CRT_SECURE_NO_WARNINGS -D_SCL_SECURE_NO_WARNINGS)

SET(SRC_LIST
	main.cpp
	TConsumerProducer.h
)

ADD_EXECUTABLE(producer_consumer ${SRC_LIST})