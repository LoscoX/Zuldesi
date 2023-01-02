cmake_minimum_required(VERSION 2.9)
project(Zuldesi)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
add_executable(Zuldesi ncurses_test.cpp)
target_link_libraries(${PROJECT_NAME} ${CURSES_LIBRARIES})
