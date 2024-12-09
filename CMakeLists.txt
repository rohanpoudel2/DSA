cmake_minimum_required(VERSION 3.8)

# Set the project name
project(EcommerceStore)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories for headers
include_directories(include)

# Specify the output directory for the build to be the build folder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Add the executable for the main project
add_executable(EcommerceStore
  src/main.cpp
  src/User.cpp
  src/Product.cpp
  src/ProductList.cpp
  src/Database.cpp
  src/ProductManager.cpp
  src/InquiryManager.cpp
  src/InquiryQueue.cpp
  src/Inquiry.cpp
  src/UserManager.cpp
  src/PromoManager.cpp
  src/CircularLinkedList.cpp
  src/Promo.cpp
  src/Menu.cpp
  src/Utils.cpp
  src/CustomQueue.cpp
)

# Find and include SQLite3
find_package(SQLite3 REQUIRED)
include_directories(${SQLite3_INCLUDE_DIRS})

# Link the main executable with the sqlite3 library
target_link_libraries(EcommerceStore PRIVATE sqlite3)

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
  tests/test_database.cpp
  tests/test_product.cpp
  tests/test_product_list.cpp
  tests/test_product_manager.cpp
  tests/test_user_manager.cpp
  tests/test_user.cpp
  tests/test_inquiry.cpp
  tests/test_inquiry_queue.cpp
  tests/test_promo.cpp
  tests/test_promo_manager.cpp
  tests/test_circular_linked_list.cpp
  tests/Environment.cpp
  src/Menu.cpp
  src/User.cpp
  src/Product.cpp
  src/ProductList.cpp
  src/Database.cpp
  src/ProductManager.cpp
  src/InquiryManager.cpp
  src/InquiryQueue.cpp
  src/Inquiry.cpp
  src/UserManager.cpp
  src/PromoManager.cpp
  src/CircularLinkedList.cpp
  src/Promo.cpp
  src/Utils.cpp
  src/CustomQueue.cpp
)

# Link GoogleTest and sqlite3 with the test executable
target_link_libraries(runTests gtest gtest_main gmock gmock_main pthread sqlite3)

# Add tests
add_test(NAME ProductTests COMMAND runTests)