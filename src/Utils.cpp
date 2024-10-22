#include "Utils.h"
#include <iostream>
#include <limits>
#include <iomanip>
#include <sstream>
#include <ctime>

#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include <iostream>

bool Utils::handleInputFailure(std::istream &input)
{
  if (input.fail())
  {
    std::cerr << "Invalid input. Please try again." << std::endl;
    input.clear();
    input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return true;
  }
  return false;
}

std::string Utils::hashPassword(const std::string &password)
{
  std::hash<std::string> hashFunction;
  size_t hashedValue = hashFunction(password);
  return std::to_string(hashedValue);
}

template <>
void Utils::promptForInput<std::string>(const std::string &message, std::string &value)
{
  std::cout << message;
  std::getline(std::cin >> std::ws, value);
}

template <>
void Utils::promptForInput<int>(const std::string &message, int &value)
{
  std::cout << message;
  std::cin >> value;
  handleInputFailure(std::cin);
}

template <>
void Utils::promptForInput<double>(const std::string &message, double &value)
{
  std::cout << message;
  std::cin >> value;
  handleInputFailure(std::cin);
}

std::string Utils::getCurrentTimestamp()
{
  std::time_t t = std::time(nullptr);
  std::tm tm = *std::localtime(&t);
  std::ostringstream oss;
  oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
  return oss.str();
}

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