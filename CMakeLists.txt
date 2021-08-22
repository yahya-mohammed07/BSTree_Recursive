cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
project(Catch2 LANGUAGES CXX)
include_directories(lib)
add_executable(${PROJECT_NAME}
  tests.cpp
  lib/bst.hpp
  lib/apology.hpp
)

find_package(Catch2)
target_link_libraries(${PROJECT_NAME} Catch2::Catch2WithMain)

