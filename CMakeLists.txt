cmake_minimum_required(VERSION 3.20.3)

project(jsoncpp)

set(PROJECT_VERSION "0.0.1")

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(src)

# Tests
add_subdirectory(test)

# Dependencies
add_subdirectory(lib/googletest)
