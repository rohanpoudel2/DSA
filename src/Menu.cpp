#include "Menu.h"
#include "ProductList.h"
#include "Database.h"

#include <string>
#include <limits>

// Handles input failures by clearing the error state and ignoring invalid input
// Precondition: stream contains input that may be invalid
// Postcondition: Error state is cleared if input was invalid, input buffer is always cleared
// Written by Rohan Poudel
bool handleInputFailure(std::istream &stream)
{
  using namespace std;
  if (stream.fail())
  {
    stream.clear();                                         // Clear the error flag
    stream.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
    cout << "Invalid input. Please enter the correct type." << endl;
    return true;
  }
  else
  {
    stream.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
    return false;
  }
}

// Function template for input validation
// Precondition: prompt_message is a valid string, input is a valid reference to a variable of type T
// Postcondition: Retrieves input from the user, ensuring valid input of the correct type
// Written by Rohan Poudel
template <typename T>
void promptForInput(const std::string &prompt_message, T &input)
{
  using namespace std;

  while (true)
  {
    cout << prompt_message;
    cin >> input;

    // Check if the input failed and handle it appropriately
    if (!handleInputFailure(cin))
      break;
  }
}

// Written by Rohan Poudel
void Menu::AddNewProduct()
{
  std::string product_name;
  double product_price;
  int product_quantity;

  promptForInput("Enter product name: ", product_name);
  promptForInput("Enter product price: ", product_price);
  promptForInput("Enter product quantity: ", product_quantity);

  Product newProduct(product_name, product_price, product_quantity); // Create a new product object
  ProductList productList;                                           // Initialize the product list
  Database db("./data/products.txt");                                // Initialize the database to save the product

  productList.addProduct(newProduct); // Add the product to the list
  db.saveProducts(productList);       // Save the updated list to the database

  std::cout << "Adding a new product..." << std::endl;
  newProduct.displayProduct();
}

// Written by Rohan Poudel
void Menu::ViewAllProducts()
{
  std::cout << "Viewing all products..." << std::endl;
  ProductList productList;
  Database db("./data/products.txt");
  db.loadProducts(productList);
  productList.displayAllProducts();
}

// Written by Rohan Poudel
void Menu::FindProduct()
{
  std::cout << "Feature coming soon..." << std::endl;
}

// Written by Rohan Poudel
void Menu::ExitMenu()
{
  std::cout << "Exiting..." << std::endl;
  exit(0);
}

// Written by Rohan Poudel
Menu::Menu()
{
  menu_options = {{{1, "Add new product", AddNewProduct},
                   {2, "View all products", ViewAllProducts},
                   {3, "Find a product", FindProduct},
                   {4, "Exit", ExitMenu}}};
}

// Written by Rohan Poudel
void Menu::displayMenu() const
{
  std::cout << "===============================" << std::endl;
  std::cout << "       E-commerce Store" << std::endl;
  std::cout << "===============================" << std::endl;
  for (const auto &option : menu_options) // Loop through the array of options and display each
  {
    std::cout << std::get<0>(option) << ". " << std::get<1>(option) << std::endl;
  }
  std::cout << "===============================" << std::endl;
  std::cout << "Enter your choice: ";
}

// Written by Rohan Poudel
void Menu::processOption() const
{
  using namespace std;

  int choice;
  cin >> choice;

  // Validate the input
  if (handleInputFailure(cin))
    return;

  // Match the choice with the menu options
  for (const auto &option : menu_options)
  {
    if (get<0>(option) == choice)
    {
      get<2>(option)(); // Execute the corresponding function
      return;
    }
  }

  cout << "Invalid option!" << endl;
}

// Written by Rohan Poudel
void Menu::startMenu() const
{
  while (true)
  {
    displayMenu();
    processOption();
  }
}