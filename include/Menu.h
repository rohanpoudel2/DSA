#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <array>
#include <functional>
#include <tuple>

class Menu
{
private:
  // Use an array to store the menu options in a tuple (MenuOption, string, function)
  std::array<std::tuple<int, std::string, std::function<void()>>, 4> menu_options;

public:
  // Default constructor
  // Precondition: None
  // Postcondition: Initializes the menu with default options (e.g., Add Product, View Products, Exit)
  Menu();

  // Displays the menu to the user
  // Precondition: None
  // Postcondition: Outputs the menu options to the console
  void displayMenu() const;

  // Processes the user's menu option choice
  // Precondition: User provides input as an integer corresponding to a menu option
  // Postcondition: Executes the function associated with the chosen menu option or displays an error if invalid
  void processOption() const;

  // Starts the menu, displaying options and processing user input
  // Precondition: None
  // Postcondition: Displays the menu and processes the user's choice in a loop
  void startMenu() const;

  // Additional Menu-specific functionality
  static void AddNewProduct();
  static void ViewAllProducts();
  static void FindProduct();
  static void ExitMenu();
};

#endif