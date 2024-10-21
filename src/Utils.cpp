#include "Utils.h"
#include <iostream>
#include <limits>
#include <iomanip>
#include <sstream>

// Handle input failure, clear errors and ignore invalid input
bool Utils::handleInputFailure(std::istream &input)
{
  if (!input)
  {
    std::cerr << "Invalid input. Please try again." << std::endl;
    input.clear();                                                   // clear error flag
    input.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
    return true;
  }
  return false;
}

// Hash the password using SHA-256
std::string Utils::hashPassword(const std::string &password)
{
  std::hash<std::string> hashFunction;
  size_t hashedValue = hashFunction(password);
  return std::to_string(hashedValue);
}

// Generic promptForInput implementation
template <>
void Utils::promptForInput(const std::string &message, std::string &value)
{
  std::cout << message;
  std::cin >> value;
}

template <>
void Utils::promptForInput(const std::string &message, double &value)
{
  std::cout << message;
  std::cin >> value;
  handleInputFailure(std::cin);
}

template <>
void Utils::promptForInput(const std::string &message, int &value)
{
  std::cout << message;
  std::cin >> value;
  handleInputFailure(std::cin);
}