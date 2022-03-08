cmake_minimum_required(VERSION 3.15)
project(BrickBreaker)

set(CMAKE_CXX_STANDARD "20")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


add_executable(Pathfinding src/main.cpp src/gameloop.cpp)

target_link_directories(Pathfinding PUBLIC ${CMAKE_SOURCE_DIR}/lib)
target_link_libraries(Pathfinding sfml-graphics sfml-system sfml-network sfml-audio sfml-window)
target_include_directories(Pathfinding PUBLIC ${CMAKE_SOURCE_DIR}/include)

