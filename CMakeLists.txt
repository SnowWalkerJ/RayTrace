cmake_minimum_required(VERSION 3.21)
project(RayTrace)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)
file(GLOB SOURCES src/Material/*.cpp src/Shape/*.cpp src/Renderer/*.cpp)
file(GLOB HEADERS include/*/*.h)
add_executable(RayTrace src/main.cpp src/random.cpp ${SOURCES} ${HEADERS})

add_subdirectory(test)
enable_testing()
