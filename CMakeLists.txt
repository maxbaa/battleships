cmake_minimum_required(VERSION 3.10)
project(Battleships)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add all source files
set(SOURCES
    main.cpp
    Game.cpp
    Human.cpp
    AI.cpp
    GameBoard.cpp
    Ship.cpp
    Server.cpp
    Client.cpp
    NetworkTransfer.cpp
)

# Add executable
add_executable(Battleships ${SOURCES})

# Boost Asio hinzufügen (ohne Linker-Bibliotheken nötig, Header-Only)
set(BOOST_ROOT "C:/Program Files/Boost/boost_1_87_0")
include_directories(${BOOST_ROOT})

# Warnings aktivieren für GCC/Clang
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(Battleships PRIVATE -Wall -Wextra -pedantic)
endif()
