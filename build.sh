#!/bin/bash

# Create build directory if it doesn't exist
if [ ! -d "build" ]; then
    mkdir build
fi

# Run CMake and build the project
cmake -S . -B build
cmake --build build