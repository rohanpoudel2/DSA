#include "Menu.h"
#include "ProductList.h"
#include "Database.h"

#include <string>
#include <limits>
#include <iostream>
#include <sstream>
#include <functional> // For std::hash

ProductList productStack;
InquiryQueue inquiryQueue;
Database db("./data/store.db");

// Handles input failures by clearing the error state and ignoring invalid input
bool handleInputFailure(std::istream &stream)
{
  if (stream.fail())
  {
    stream.clear();
    stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Invalid input. Please enter the correct type." << std::endl;
    return true;
  }
  else
  {
    stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return false;
  }
}

// Function template for input validation
template <typename T>
void promptForInput(const std::string &prompt_message, T &input)
{
  while (true)
  {
    std::cout << prompt_message;
    std::cin >> input;
    if (!handleInputFailure(std::cin))
      break;
  }
}

// Menu constructor
Menu::Menu() : db("./data/store.db"), currentUser() // Initialize currentUser with default constructor
{
  Login(); // Prompt user to log in

  if (currentUser.isAdmin())
  {
    menu_options = {{{1, "Add new product", std::bind(&Menu::AddNewProduct, this)},
                     {2, "View all products", std::bind(&Menu::ViewAllProducts, this)},
                     {3, "Undo last added product", std::bind(&Menu::UndoLastAddedProduct, this)},
                     {4, "Exit", std::bind(&Menu::ExitMenu, this)}}};
  }
  else
  {
    menu_options = {{{1, "Add new inquiry", std::bind(&Menu::AddNewInquiry, this)},
                     {2, "View inquiries", std::bind(&Menu::ViewInquiries, this)},
                     {3, "Process inquiry", std::bind(&Menu::ProcessInquiry, this)},
                     {4, "Exit", std::bind(&Menu::ExitMenu, this)}}};
  }

  db.loadProducts(productStack); // Load any products from the database
}

void Menu::displayMenu() const
{
  clearConsole();
  std::cout << "===============================" << std::endl;
  std::cout << "       E-commerce Store" << std::endl;
  std::cout << "===============================" << std::endl;
  for (const auto &option : menu_options)
  {
    std::cout << std::get<0>(option) << ". " << std::get<1>(option) << std::endl;
  }
  std::cout << "===============================" << std::endl;
  std::cout << "Enter your choice: ";
}

void Menu::processOption() const
{
  int choice;
  std::cin >> choice;

  if (handleInputFailure(std::cin))
    return;

  for (const auto &option : menu_options)
  {
    if (std::get<0>(option) == choice)
    {
      std::get<2>(option)();
      return;
    }
  }

  std::cout << "Invalid option!" << std::endl;
}

void Menu::startMenu()
{
  while (true)
  {
    displayMenu();
    processOption();
  }
}

// Handle login of user
void Menu::Login()
{
  std::string email, password;
  std::cout << "Welcome! Are you logging in as (1) Admin or (2) Customer? ";
  int roleOption;
  std::cin >> roleOption;

  if (roleOption == 1) // Admin login
  {
    promptForInput("Enter admin password: ", password);
    if (db.verifyAdminPassword(hashPassword(password)))
    {
      currentUser = User("Admin", "admin@store.com", "admin", password);
      std::cout << "Admin access granted!" << std::endl;
    }
    else
    {
      std::cerr << "Invalid admin credentials!" << std::endl;
    }
  }
  else // Customer login
  {
    promptForInput("Enter your email: ", email);
    currentUser = db.getCustomerByEmail(email);

    if (currentUser.getEmail().empty())
    {
      std::string name;
      promptForInput("Enter your name: ", name);
      std::string plainPassword;
      promptForInput("Enter your password: ", plainPassword);

      currentUser = User(name, email, "customer", hashPassword(plainPassword));
      db.addUser(currentUser);
      std::cout << "Customer registered!" << std::endl;
    }
    else
    {
      std::cout << "Welcome back, " << currentUser.getName() << "!" << std::endl;
    }
  }
}

// Admin functionality (Add product, Undo, View)
void Menu::AddNewProduct()
{
  clearConsole();
  std::string product_name;
  double product_price;
  int product_quantity;

  promptForInput("Enter product name: ", product_name);
  promptForInput("Enter product price: ", product_price);
  promptForInput("Enter product quantity: ", product_quantity);

  Product newProduct(product_name, product_price, product_quantity);
  productStack.pushProduct(newProduct);
  db.saveProducts(productStack, "replace");

  std::cout << "Adding a new product..." << std::endl;
  newProduct.displayProduct();
}

void Menu::UndoLastAddedProduct()
{
  if (!productStack.isEmpty())
  {
    Product removedProduct = productStack.popProduct();
    std::cout << "Undoing the last added product: " << removedProduct.getName() << std::endl;
    db.saveProducts(productStack, "replace");
  }
  else
  {
    std::cout << "No products to undo!" << std::endl;
  }
}

void Menu::ViewAllProducts()
{
  std::cout << "Viewing all products..." << std::endl;
  productStack.displayAllProducts();
}

// Customer functionality (Add inquiry, View inquiry, Process inquiry)
void Menu::AddNewInquiry()
{
  std::string message;
  promptForInput("Enter inquiry message: ", message);

  InquiryNode inquiry("", currentUser.getEmail(), message);
  db.saveInquiryToDB(inquiry, currentUser.getId());

  std::cout << "Inquiry added successfully!\n";
}

void Menu::ProcessInquiry()
{
  InquiryNode *inquiry = db.loadNextInquiryFromDB();
  if (inquiry != nullptr)
  {
    std::cout << "Processing inquiry from: " << inquiry->inquiryMessage << std::endl;
    delete inquiry;
  }
  else
  {
    std::cout << "No inquiries to process.\n";
  }
}

void Menu::ViewInquiries()
{
  inquiryQueue.displayAllInquiries();
}

void Menu::clearConsole() const
{
  // std::cout << "\033[2J\033[H";
}

void Menu::ExitMenu()
{
  std::cout << "Exiting..." << std::endl;
  exit(0);
}