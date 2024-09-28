#include "Menu.h"
#include "ProductList.h"
#include "Database.h"

#include <string>
#include <limits>

// Function to handle input failure
void handleInputFailure()
{
  using namespace std;
  cin.clear();
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  cout << "Invalid input. Please enter the correct type." << endl;
}

// Function template for input validation
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
      handleInputFailure();
    }
    else
    {
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      break;
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

  Product newProduct(product_name, product_price, product_quantity);
  ProductList productList;
  Database db("./data/products.txt");

  productList.addProduct(newProduct);
  db.saveProducts(productList);
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
  for (const auto &option : menu_options)
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

  if (cin.fail())
  {
    handleInputFailure();
    return;
  }

  for (const auto &option : menu_options)
  {
    if (get<0>(option) == choice)
    {
      get<2>(option)();
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