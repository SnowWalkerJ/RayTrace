cmake_minimum_required(VERSION 3.21)
project(RayTrace)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -msse4.1")

include_directories(include)
file(GLOB SOURCES src/*/*.cpp)
file(GLOB HEADERS include/*/*.h)
add_executable(RayTrace src/main.cpp src/random.cpp ${SOURCES} ${HEADERS})

add_subdirectory(test)
enable_testing()
