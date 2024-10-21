#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <limits>
#include <string>
#include <functional>

class Utils
{
public:
  // Hash a password using std::hash (replace this with more secure hash if needed)
  static std::string hashPassword(const std::string &password);

  // Handles input failures by clearing the error state and ignoring invalid input
  static bool handleInputFailure(std::istream &stream);

  // Template function for input validation
  template <typename T>
  static void promptForInput(const std::string &prompt_message, T &input)
  {
    while (true)
    {
      std::cout << prompt_message;
      std::cin >> input;
      if (!handleInputFailure(std::cin))
        break;
    }
  }
};

#endif