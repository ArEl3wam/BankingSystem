#!/bin/bash

# Function to clean the build directory
clean_build() {
    echo "Cleaning build directory..."
    rm -rf build
    echo "Build directory cleaned."
}

# Function to build the project
build_project() {
    echo "Building project..."
    mkdir -p build
    cmake -G Ninja -B build -S . -DCMAKE_C_COMPILER="C:/Program Files/LLVM/bin/clang.exe" -DCMAKE_CXX_COMPILER="C:/Program Files/LLVM/bin/clang++.exe" -DCMAKE_CXX_FLAGS="-target x86_64-w64-mingw32"  -DCMAKE_BUILD_TYPE=Release
    cmake --build ./build
}

# Check for command-line arguments
if [ "$1" == "clean" ]; then
    clean_build
elif [ "$1" == "build" ]; then
    build_project
else
    echo "Usage: $0 [clean|build]"
    echo "  clean - Remove the build directory."
    echo "  build - Build the project."
fi