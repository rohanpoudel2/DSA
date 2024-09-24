#include <iostream>
#include "Product.h"
#include "ProductList.h"
#include "Database.h"

void showMenu()
{
  std::cout << "===============================" << std::endl;
  std::cout << "       E-commerce Store" << std::endl;
  std::cout << "===============================" << std::endl;
  std::cout << "1. Add new product" << std::endl;
  std::cout << "2. View all products" << std::endl;
  std::cout << "3. Find a product" << std::endl;
  std::cout << "4. Exit" << std::endl;
  std::cout << "===============================" << std::endl;
  std::cout << "Enter your choice (1-4): ";
}

int main()
{
  ProductList productList;
  Database db("../data/products.txt");

  db.loadProducts(productList);

  int choice;
  do
  {
    showMenu();
    std::cin >> choice;

    switch (choice)
    {
    case 1:
    {
      std::string name;
      double price;
      int quantity;

      std::cout << "Enter product name: ";
      std::cin >> name;
      std::cout << "Enter product price: ";
      std::cin >> price;
      std::cout << "Enter product quantity: ";
      std::cin >> quantity;

      Product newProduct(name, price, quantity);
      productList.addProduct(newProduct);
      db.saveProducts(productList);

      break;
    }
    case 2:
      std::cout << "Feature coming soon!" << std::endl;
      break;
    case 3:
      std::cout << "Feature coming soon!" << std::endl;
      break;
    case 4:
      std::cout << "Exiting the program. Goodbye!" << std::endl;
      break;
    default:
      std::cout << "Invalid choice, please try again." << std::endl;
    }
  } while (choice != 4);

  return 0;
}