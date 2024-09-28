#!/bin/bash

# Create build directory if it doesn't exist
if [ ! -d "build" ]; then
    mkdir build
fi

# Run CMake and build the project
cd build
cmake ..
cmake --build .