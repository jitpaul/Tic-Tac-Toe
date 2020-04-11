cmake_minimum_required(VERSION 3.5)

project(tictactoe CXX)

add_library(tictactoe "")

target_sources(
    tictactoe
    PRIVATE
        tictactoe.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/tictactoe.h
)

target_include_directories(
    tictactoe
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)

add_executable(
    main
    main.cpp)
  
target_link_libraries(
    main
    tictactoe)