cmake_minimum_required(VERSION 3.8)

# Set the project name
project(EcommerceStore)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON) # Ensure C++17 is strictly enforced

# Include directories for headers
include_directories(include)

# Specify the output directory for the build to be the build folder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Add the executable for the main project
add_executable(EcommerceStore
  src/main.cpp
  src/Product.cpp
  src/ProductList.cpp
  src/Database.cpp
  src/Menu.cpp
)

# Add GoogleTest
include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)

# Download and configure GoogleTest
FetchContent_MakeAvailable(googletest)

# Enable testing
enable_testing()

# Add the test executable
add_executable(runTests
    tests/test_product.cpp
    tests/test_productlist.cpp
    tests/test_database.cpp
    tests/test_menu.cpp
    src/Product.cpp
    src/ProductList.cpp
    src/Database.cpp
    src/Menu.cpp
)

# Link GoogleTest with the test executable
target_link_libraries(runTests gtest gtest_main gmock gmock_main)

# Add tests
add_test(NAME ProductTests COMMAND runTests)