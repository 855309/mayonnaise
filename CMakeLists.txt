cmake_minimum_required(VERSION 2.8)
project(mayonnaise)

set(CMAKE_CXX_STANDARD 17)

# set(GCC_COVERAGE_COMPILE_FLAGS "")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

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

target_link_libraries(mayonnaise readline)