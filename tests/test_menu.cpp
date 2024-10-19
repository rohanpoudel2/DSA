// Generated with AI assistance (ChatGPT)
#include <gtest/gtest.h>
#include <sstream>
#include <iostream>
#include "Menu.h"

// Helper function to simulate user input
void simulateInput(const std::string &input)
{
  std::istringstream input_stream(input);
  std::cin.rdbuf(input_stream.rdbuf()); // Redirect input to simulate user input
}

// Test the Menu class for displaying the menu
TEST(MenuTest, DisplayMenuTest)
{
  Menu menu; // Use the real class

  testing::internal::CaptureStdout(); // Capture console output
  menu.displayMenu();                 // Call the actual displayMenu function
  std::string output = testing::internal::GetCapturedStdout();

  std::string expected_output =
      "===============================\n"
      "       E-commerce Store\n"
      "===============================\n"
      "1. Add new product\n"
      "2. View all products\n"
      "3. Find a product\n"
      "4. Undo last added product\n" // Ensure Undo is part of the menu
      "5. Exit\n"
      "===============================\n"
      "Enter your choice: ";

  EXPECT_EQ(output, expected_output); // Compare the captured output to the expected output
}

// Test processing a valid menu option (e.g., Add new product)
TEST(MenuTest, ProcessValidOptionTest)
{
  Menu menu;

  // Simulate the user selecting "Add new product"
  simulateInput("1\n");

  testing::internal::CaptureStdout(); // Capture the output
  menu.processOption();
  std::string output = testing::internal::GetCapturedStdout();

  // Verify the expected output for adding a new product
  EXPECT_TRUE(output.find("Enter product name:") != std::string::npos);
}

// Test processing an invalid menu option
TEST(MenuTest, ProcessInvalidOptionTest)
{
  Menu menu;

  // Simulate the user entering an invalid option (e.g., 10)
  simulateInput("10\n");

  testing::internal::CaptureStdout(); // Capture the output
  menu.processOption();
  std::string output = testing::internal::GetCapturedStdout();

  // Check that the output contains the invalid option message
  EXPECT_EQ(output, "Invalid option!\n");
}

// Test starting the menu and processing the exit option
TEST(MenuTest, StartMenuExitTest)
{
  Menu menu;

  // Simulate the user selecting the "Exit" option
  simulateInput("5\n");

  testing::internal::CaptureStdout(); // Capture the output
  menu.startMenu();
  std::string output = testing::internal::GetCapturedStdout();

  // Verify that the correct exit message is displayed
  EXPECT_TRUE(output.find("Exiting...") != std::string::npos);
}

// Test processing the undo operation
TEST(MenuTest, ProcessUndoLastAddedProduct)
{
  Menu menu;

  // Simulate the user selecting "Undo last added product"
  simulateInput("4\n");

  testing::internal::CaptureStdout(); // Capture the output
  menu.processOption();
  std::string output = testing::internal::GetCapturedStdout();

  // Verify the undo operation message is displayed correctly
  EXPECT_TRUE(output.find("Undoing the last added product:") != std::string::npos || output.find("No products to undo!") != std::string::npos);
}