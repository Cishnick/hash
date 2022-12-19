cmake_minimum_required(VERSION 3.10)

project(Hash)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB SRC_FILES
     "./src/*.h"
     "./src/*.cpp"
)

add_executable(Hash ${SRC_FILES})