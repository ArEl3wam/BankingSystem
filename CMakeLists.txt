cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -target x86_64-w64-mingw32")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -target x86_64-w64-mingw32")
project(BankingSystem LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_PARALLEL_LEVEL 4 CACHE STRING "Number of parallel jobs for builds")

add_subdirectory(cli)
add_subdirectory(core_model)
add_subdirectory(common)


# Executable target
add_executable(bank-system
    main.cpp
)

# Link libraries from subdirectories
target_link_libraries(bank-system PRIVATE cli core_model common)

# Include directories for headers
target_include_directories(bank-system PRIVATE
    cli
    core_model
    common
)
