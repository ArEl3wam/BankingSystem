cmake_minimum_required(VERSION 3.15)
project(BankingSystem LANGUAGES CXX)

# Set default build type to Debug if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
    # Provide options for the build type in the GUI
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release")
endif()

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_PARALLEL_LEVEL 4 CACHE STRING "Number of parallel jobs for builds")

# Debug-specific compiler flags
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Configuring DEBUG build")
    # Flags for GCC/Clang
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        add_compile_options(-g -O0 -Wall -Wextra -pedantic)
    # Flags for MSVC
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        add_compile_options(/Zi /Od /RTC1)
    endif()
endif()

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