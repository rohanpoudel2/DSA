#include "Menu.h"
#include "ProductList.h"
#include "Database.h"

#include <string>
#include <limits>

// Generated with AI assistance (ChatGPT)
// I wanted to create a template function to follow DRY rule
template <typename T>
void promptForInput(const std::string &prompt_message, T &input)
{
  using namespace std;

  while (true)
  {
    cout << prompt_message;
    cin >> input;

    // Check if the input failed (wrong type)
    if (cin.fail())
    {
      cin.clear();                                         // Clear the error flag
      cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the invalid input
      cout << "Invalid input. Please enter the correct type." << endl;
    }
    else
    {
      cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
      break;                                               // Valid input, break out of the loop
    }
  }
}

// Written by Rohan Poudel
void Menu::AddNewProduct()
{
  std::cout << "Adding a new product..." << std::endl;

  std::string product_name;
  promptForInput("Enter product name: ", product_name);

  double product_price;
  promptForInput("Enter product price: ", product_price);

  int product_quantity;
  promptForInput("Enter product quantity: ", product_quantity);

  std::cout << "Product added: " << product_name << ", Price: " << product_price << ", Quantity: " << product_quantity << std::endl;

  Product newProduct(product_name, product_price, product_quantity); // Create a new product
  ProductList productList;                                           // Create a new product list
  Database db("./data/products.txt");                                // Create a database object for saving products

  productList.addProduct(newProduct); // Add the product to the product list
  db.saveProducts(productList);       // Save the product list to the database
}

// Written by Rohan Poudel
void Menu::ViewAllProducts()
{
  std::cout << "Viewing all products..." << std::endl;
}

// Written by Rohan Poudel
void Menu::FindProduct()
{
  std::cout << "Finding a product..." << std::endl;
}

// Written by Rohan Poudel
void Menu::ExitMenu()
{
  std::cout << "Exiting..." << std::endl;
  exit(0);
}

// Written by Rohan Poudel
Menu::Menu() : menu_options({{"Add new product", {1, AddNewProduct}},
                             {"View all products", {2, ViewAllProducts}},
                             {"Find a product", {3, FindProduct}},
                             {"Exit", {4, ExitMenu}}}) {}

// Written by Rohan Poudel
void Menu::displayMenu() const
{
  std::cout << "===============================" << std::endl;
  std::cout << "       E-commerce Store" << std::endl;
  std::cout << "===============================" << std::endl;
  for (const auto &option : menu_options) // Loop through the menu options and display them
  {
    std::cout << std::get<0>(option.second) << ". " << option.first << std::endl;
  }
  std::cout << "===============================" << std::endl;
  std::cout << "Enter your choice: ";
}

// Written by Rohan Poudel
int Menu::processOption() const
{
  using namespace std;

  int option;
  cin >> option;

  for (const auto &opt : menu_options) // Loop through the menu options
  {
    if (get<0>(opt.second) == option) // Check if the selected option matches
    {
      get<1>(opt.second)(); // Execute the corresponding function
      return 1;
    }
  }

  cout << "Invalid option!" << endl;
  return 0;
}

// Written by Rohan Poudel
void Menu::startMenu() const
{
  displayMenu();   // Display the menu
  processOption(); // Process the selected option
}