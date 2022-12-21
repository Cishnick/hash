cmake_minimum_required(VERSION 3.10)

project(Hash)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)


enable_testing()

add_subdirectory(src)
add_subdirectory(tst)
