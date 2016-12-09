cmake_minimum_required(VERSION 3.5)
project(cpp_project)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
file(GLOB files "*.h" "*.cpp")
add_executable(cpp_project ${files} ${SOURCE_FILES})