#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <iostream>

class Utils
{
public:
  static bool handleInputFailure(std::istream &input);
  static std::string hashPassword(const std::string &password);

  // Function declarations for promptForInput (template)
  template <typename T>
  static void promptForInput(const std::string &message, T &value);

  static std::string getCurrentTimestamp();
  static std::string getDatabasePath(std::string &environment);

  static bool isValidEmail(const std::string &email);
};

// Template declaration (but not specialized here in the header)
template <typename T>
void Utils::promptForInput(const std::string &message, T &value)
{
  std::cout << message;
  std::cin >> value;
  handleInputFailure(std::cin);
}

#endif // UTILS_H