cmake_minimum_required(VERSION 3.24)
project(Zuldesi)

set(CMAKE_CXX_STANDARD 14)
target_link_libraries(ncurses_test.cpp)
include_directories("/ncurses")
add_library()
add_executable(Zuldesi  ncurses_test.cpp)
