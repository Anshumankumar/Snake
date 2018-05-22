cmake_minimum_required(VERSION 2.8)
project(Snake)

find_package(Curses REQUIRED)
add_executable(snake Snake.cpp)
target_link_libraries( snake ${CURSES_LIBRARIES})
