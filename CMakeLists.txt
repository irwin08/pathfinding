cmake_minimum_required(VERSION 3.15)
project(BrickBreaker)

set(CMAKE_CXX_STANDARD "20")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(Pathfinding src/main.cpp src/gameloop.cpp src/map.cpp)

target_link_libraries(Pathfinding sfml-graphics sfml-system sfml-network sfml-audio sfml-window)

