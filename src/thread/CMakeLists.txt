file(GLOB CPP *.cpp)
file(GLOB HPP *.hpp)

ADD_EXECUTABLE(thread ${CPP} ${HPP}
)
