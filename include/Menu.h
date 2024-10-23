#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <array>
#include <functional>
#include <tuple>
#include "UserManager.h"
#include "ProductManager.h"
#include "InquiryManager.h"
#include "InquiryQueue.h"
#include "User.h"
#include "ProductList.h"
#include "PromoManager.h"

class Menu
{
private:
  // Admin menu options
  // Precondition: Admin user must be logged in
  // Postcondition: A Vector of available actions for the admin is created
  std::vector<std::tuple<int, std::string, std::function<void()>>> admin_menu_options;

  // Customer menu options
  // Precondition: Customer user must be logged in
  // Postcondition: A Vector of available actions for the customer is created
  std::vector<std::tuple<int, std::string, std::function<void()>>> customer_menu_options;

  // Objects to manage database-related operations for users, products, inquiries, and promotions.
  // Preconditions: Each of these managers must be initialized with a valid database path.
  // Postconditions: The managers are ready to handle their respective data interactions.
  UserManager userManager;
  ProductManager productManager;
  InquiryManager inquiryManager;
  InquiryQueue inquiryQueue;
  PromoManager promoManager;

  // Represents the current logged-in user.
  // Precondition: User must have logged in successfully.
  // Postcondition: The current user's details are stored.
  User currentUser;

  // Stack to hold products for managing the product list.
  // Precondition: Products must have been added to the system.
  // Postcondition: The products are stored in a LIFO (Last In, First Out) manner.
  ProductList productStack;

  // Database file path.
  // Precondition: Must be a valid path to the database.
  // Postcondition: The database path is set for future use.
  std::string dbPath;

  // Initializes the menu options based on the user's role (Admin or Customer).
  // Precondition: User must be logged in.
  // Postcondition: The appropriate menu options for the user are created.
  void initializeMenuOptions();

  // Handles admin login process.
  // Precondition: Admin password must be provided.
  // Postcondition: Verifies and grants access to admin if the password is correct.
  void handleAdminLogin(std::string &password);

  // Handles customer login process.
  // Precondition: Customer email and password must be provided.
  // Postcondition: Verifies and grants access if customer exists, or registers a new customer.
  void handleCustomerLogin(std::string &email, std::string &password);

  // Registers a new customer.
  // Precondition: Email must not exist in the system.
  // Postcondition: Creates a new customer record in the database.
  void registerNewCustomer(const std::string &email);

  // Authenticates a returning customer.
  // Precondition: Customer's password must be provided.
  // Postcondition: Verifies and grants access if the password is correct.
  void authenticateReturningCustomer(std::string &password);

public:
  // Constructor to initialize the menu and all associated managers.
  // Precondition: The database file path must be valid.
  // Postcondition: Initializes menu-related components.
  Menu();

  // Displays the available menu options to the user.
  // Precondition: The user must be logged in.
  // Postcondition: The menu is printed to the console.
  void displayMenu() const;

  // Processes the menu option selected by the user.
  // Precondition: A valid choice (integer) must be entered.
  // Postcondition: Executes the corresponding menu action.
  void processOption() const;

  // Starts the main menu loop, displaying the menu and processing user inputs until exit.
  // Precondition: User must be logged in.
  // Postcondition: Menu keeps running until exit is selected.
  void startMenu();

  // Prompts the user to log in, either as an admin or customer.
  // Precondition: The user must provide login details (email, password, etc.).
  // Postcondition: The user is authenticated and logged in.
  void Login();

  // Admin function to add a new product to the store.
  // Precondition: The product name, price, and quantity must be provided.
  // Postcondition: The product is added to the store and saved in the database.
  void AddNewProduct();

  // Admin function to view all available products.
  // Precondition: Admin must be logged in.
  // Postcondition: Displays the list of products in the store.
  void ViewAllProducts();

  // Admin function to undo the last added product.
  // Precondition: There must be at least one product in the list.
  // Postcondition: The last added product is removed from the list and the database is updated.
  void UndoLastAddedProduct();

  // Customer function to add a new inquiry.
  // Precondition: Customer must be logged in and provide an inquiry message.
  // Postcondition: The inquiry is added to the system and saved in the database.
  void AddNewInquiry();

  // Admin function to process inquiries from customers.
  // Precondition: Admin must be logged in, and there must be pending inquiries.
  // Postcondition: Admin reviews and responds to inquiries.
  void ProcessInquiry();

  // Customer function to view their inquiries.
  // Precondition: Customer must be logged in.
  // Postcondition: Displays the customer's inquiries from the database.
  void ViewInquiries();

  // Getter for the database path.
  // Precondition: Database path must be valid.
  // Postcondition: Returns the current database path.
  std::string getDbPath() const { return dbPath; }

  // Setter for the database path.
  // Precondition: A valid database path must be provided.
  // Postcondition: Sets the new database path.
  void setDbPath(const std::string &path) { dbPath = path; }

  // Customer function to spin the wheel for a discount promo.
  // Precondition: Customer must be logged in and not already have a promo.
  // Postcondition: Generates and saves a discount promo for the customer.
  void SpinWheel();

  // Exits the menu and terminates the program.
  // Precondition: The user selects the exit option.
  // Postcondition: The program terminates.
  void ExitMenu();
};

#endif