cmake_minimum_required(VERSION 3.22)

project(Tic-Tac-Toe CXX)
set(CMAKE_CXX_STANDARD 17)

set(TTT_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

set(TTT_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")


add_executable(Tic-Tac-Toe ${TTT_SOURCES})
target_include_directories(Tic-Tac-Toe PUBLIC ${TTT_INCLUDE_DIR})