cmake_minimum_required(VERSION 3.24)
project(Zuldesi)

set(CMAKE_CXX_STANDARD 14)
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
add_executable(Zuldesi ncurses_test.cpp)
target_link_libraries(Zuldesi ${CURSES_LIBRARIES})

