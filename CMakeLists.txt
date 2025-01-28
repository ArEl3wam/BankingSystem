cmake_minimum_required(VERSION 3.15)
project(BankingSystem LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Executable target
add_executable(bank-system
    src/main.cpp
)