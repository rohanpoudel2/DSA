#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include "Product.h"
#include "ProductList.h"

class Database
{
private:
  std::string sourceFile; // The source path where products will be saved

public:
  // Constructor
  // Precondition: filename must be a valid path to a file
  // Postcondition: Initializes the Database with the given file for saving products
  Database(const std::string &filename);

  // Saves all products from the ProductList to the file
  // Precondition: productList contains valid product data
  // Postcondition: Appends all products in the list to the file in this format: (name, price, quantity)
  void saveProducts(const ProductList &productList, const std::string &mode = "append");

  // Loads all products from the file into the product list
  // Precondition: The file specified by the sourceFile path exists and is readable
  // Postcondition: Populates product list with products loaded from the file
  void loadProducts(ProductList &productList);
};

#endif