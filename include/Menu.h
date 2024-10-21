#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <array>
#include <functional>
#include <tuple>
#include "User.h"
#include "Database.h"
#include "../utils/Utilities.h"

class Menu
{
private:
  // Array to store the menu options: each option consists of an int (option number),
  // a string (menu description), and a function (corresponding action to be executed)
  std::array<std::tuple<int, std::string, std::function<void()>>, 6> menu_options;

  Database db;
  User currentUser;

public:
  // Constructor to initialize the menu with user-based options
  Menu();

  // Displays the menu to the user
  void displayMenu() const;

  // Processes the user's menu option choice
  void processOption() const;

  // Starts the menu and processes user input
  void startMenu();

  // Function to prompt the login of a user
  void Login();

  // Admin functions
  void AddNewProduct();
  void ViewAllProducts();
  void UndoLastAddedProduct();

  // Customer-specific functions
  void AddNewInquiry();
  void ProcessInquiry();
  void ViewInquiries();

  void clearConsole() const;

  // Function to exit the menu
  void ExitMenu();
};

#endif