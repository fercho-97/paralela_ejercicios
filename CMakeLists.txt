cmake_minimum_required(VERSION 3.28)

project(test)
find_package(fmt)
find_package(SFML)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")

add_executable(test main.cpp)
target_link_libraries(test fmt::fmt sfml::sfml)