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
