cmake_minimum_required(VERSION 2.8)

project(sqlitecpp)

add_definitions(-std=c++11)

set(CMAKE_CXX_FLAGS_DEBUG "-g -DDEBUG")

include_directories("./include/sq")

file(GLOB src "./src/*.cpp")

add_library(sqlitecpp ${src})
