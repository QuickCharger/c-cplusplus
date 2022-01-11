cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(Socket)

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")
include(AddTarget)
include(AutoFiles)

add_definitions(-D_UNICODE -D_CRT_SECURE_NO_WARNINGS -D_SCL_SECURE_NO_WARNINGS)
add_subdirectory(client)
add_subdirectory(server)
add_subdirectory(server_select)
