INCLUDE_DIRECTORIES(
	${CMAKE_CURRENT_SOURCE_DIR}
)

ADD_EXECUTABLE(mvc
	main.cpp
	common.h
	controller.h	controller.cpp
	model.h		model.cpp
	view.h		view.cpp
)
