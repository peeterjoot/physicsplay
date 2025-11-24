cmake_minimum_required(VERSION 3.28)
project(ModuleExample LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(my_lib)
target_sources(my_lib
  PUBLIC
  FILE_SET CXX_MODULES FILES
  hello.cppm
PRIVATE
  hello_impl.cpp
)

add_executable(app main.cpp)
target_link_libraries(app PRIVATE my_lib)
