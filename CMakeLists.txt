cmake_minimum_required(VERSION 3.0)
project(bowling)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} test.cpp catch_amalgamated.cpp) 