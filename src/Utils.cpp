#include "Utils.h"
#include <iostream>
#include <limits>
#include <iomanip>
#include <sstream>
#include <ctime>

#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include <iostream>

// Handle input failure, clear errors and ignore invalid input
bool Utils::handleInputFailure(std::istream &input)
{
  if (input.fail())
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

// Specialization for `std::string` (to handle spaces properly)
template <>
void Utils::promptForInput<std::string>(const std::string &message, std::string &value)
{
  std::cout << message;
  std::getline(std::cin >> std::ws, value); // std::getline handles spaces in input
}

// Specialization for `int`
template <>
void Utils::promptForInput<int>(const std::string &message, int &value)
{
  std::cout << message;
  std::cin >> value;
  handleInputFailure(std::cin);
}

// Specialization for `double`
template <>
void Utils::promptForInput<double>(const std::string &message, double &value)
{
  std::cout << message;
  std::cin >> value;
  handleInputFailure(std::cin);
}

// Function to get the current timestamp as a string
std::string Utils::getCurrentTimestamp()
{
  std::time_t t = std::time(nullptr);
  std::tm tm = *std::localtime(&t);
  std::ostringstream oss;
  oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S"); // Format timestamp
  return oss.str();
}

// Function to get the database path from a config file
std::string Utils::getDatabasePath(std::string &environment)
{
  FILE *fp = fopen("config.json", "r");
  if (!fp)
  {
    throw std::runtime_error("Could not open config file.");
  }

  char readBuffer[65536];
  rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
  rapidjson::Document d;
  d.ParseStream(is);
  fclose(fp);

  if (d.HasParseError())
  {
    throw std::runtime_error("Error parsing the config file.");
  }

  if (d.HasMember("db_path") && d["db_path"].HasMember(environment.c_str()))
  {
    return d["db_path"][environment.c_str()].GetString();
  }
  else
  {
    throw std::runtime_error("Invalid config file format.");
  }
}