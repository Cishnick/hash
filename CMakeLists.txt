cmake_minimum_required(VERSION 3.10)

project(Hash)

file(GLOB SRC_FILES
     "./src/*.h"
     "./src/*.cpp"
)

add_executable(Hash ${SRC_FILES})