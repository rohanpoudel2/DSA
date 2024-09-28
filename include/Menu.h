#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <array>
#include <functional>
#include <tuple>

class Menu
{
private:
  // Array to store the menu options: each option consists of an int (option number),
  // a string (menu description), and a function (corresponding action to be executed)
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
  // Function to add a new product to the product list
  // Precondition: User must input valid product details (name, price, quantity)
  // Postcondition: The new product is added to the product list and saved to the database
  static void AddNewProduct();

  // Function to view all products (currently a placeholder)
  // Precondition: None
  // Postcondition: Displays a message indicating viewing functionality
  static void ViewAllProducts();

  // Function to find a specific product (currently a placeholder)
  // Precondition: None
  // Postcondition: Displays a message indicating the search functionality
  static void FindProduct();

  // Function to exit the menu
  // Precondition: None
  // Postcondition: Terminates the program
  static void ExitMenu();
};

#endif