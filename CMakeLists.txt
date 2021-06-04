cmake_minimum_required(VERSION 3.19)
project(mayonnaise)

set(CMAKE_CXX_STANDARD 17)

add_executable(
    mayonnaise
    src/builtin.cpp
    src/construct.cpp
    src/error.cpp
    src/file.cpp
    src/interpreter.cpp
    src/parser.cpp
    src/runtime.cpp
    src/strh.cpp
    src/versioncontrol.cpp
)