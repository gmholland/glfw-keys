cmake_minimum_required(VERSION 3.17)
project(tutorial)

set(CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
message(${CMAKE_BINARY_DIR})

set(CMAKE_CXX_STANDARD 14)

find_package(fmt REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glad REQUIRED)

add_executable(tutorial main.cpp)
target_link_libraries(tutorial
  PRIVATE
    fmt::fmt
    glfw::glfw
    glad::glad
)
