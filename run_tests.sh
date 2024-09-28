#!/bin/bash

# Build the project (in case it's not already built)
./build.sh

rm ./data/test_products.txt

# Run the tests from the root directory
./build/runTests