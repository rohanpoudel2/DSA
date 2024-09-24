cmake_minimum_required(VERSION 3.10)

# Set the project name
project(EcommerceStore)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)

# Include directories for headers
include_directories(include)

# Add the executable for the main project
add_executable(EcommerceStore
    src/main.cpp
    src/Product.cpp
    src/ProductList.cpp
    src/Database.cpp
)

# Add GoogleTest
include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.11.0
)

# Download and configure GoogleTest
FetchContent_MakeAvailable(googletest)

# Enable testing
enable_testing()

# Add the test executable
add_executable(runTests
    tests/test_product.cpp
    tests/test_productlist.cpp
    src/Product.cpp
    src/ProductList.cpp
)

# Link GoogleTest with the test executable
target_link_libraries(runTests gtest gtest_main)

# Add tests
add_test(NAME ProductTests COMMAND runTests)