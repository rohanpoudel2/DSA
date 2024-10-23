#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <iostream>

class Utils
{
public:
  // Method to handle input failure
  // Precondition: input is an input stream object (e.g., std::cin)
  // Postcondition: returns true if input fails (e.g., invalid data type); otherwise, returns false
  static bool handleInputFailure(std::istream &input);

  // Method to hash a password using the SHA-256 algorithm
  // Precondition: password is a non-empty string
  // Postcondition: returns the hashed version of the input password as a string
  static std::string hashPassword(const std::string &password);

  // Method to prompt the user for input
  // Precondition: message is a non-empty string, value is of a valid input type
  // Postcondition: prompts the user with the message and stores the input value
  template <typename T>
  static void promptForInput(const std::string &message, T &value);

  // Method to get the current timestamp
  // Precondition: none
  // Postcondition: returns the current timestamp as a string in the format YYYY-MM-DD HH:MM:SS
  static std::string getCurrentTimestamp();

  // Method to get the path to the database based on the environment
  // Precondition: environment is a reference to a string specifying the environment (e.g., "development")
  // Postcondition: returns the path to the database based on the specified environment
  static std::string getDatabasePath(std::string &environment);

  // Method to check if a string is a valid email
  // Precondition: email is a non-empty string
  // Postcondition: returns true if the email follows a valid format; otherwise, returns false
  static bool isValidEmail(const std::string &email);
};

template <typename T>
void Utils::promptForInput(const std::string &message, T &value)
{
  std::cout << message;
  std::cin >> value;
  handleInputFailure(std::cin);
}

#endif