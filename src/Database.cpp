#include "Database.h"
#include <fstream>
#include <iostream>
#include <filesystem>
#include <sstream>

// Constructor initializes the database with the given file path
Database::Database(const std::string &filename) : sourceFile(filename) {}

// Save only the top product to the file (stack-like behavior)
void Database::saveProducts(const ProductList &productList, const std::string &mode)
{
  std::ofstream outFile(sourceFile, mode == "replace" ? std::ios::trunc : std::ios::app);
  if (!outFile)
  {
    std::cerr << "Unable to open file: " << sourceFile << std::endl;
    return;
  }

  // If appending, only save the top product
  if (mode == "append" && productList.getHead() != nullptr)
  {
    ProductList::Node *topProduct = productList.getHead();
    outFile << topProduct->product.getName() << ","
            << topProduct->product.getPrice() << ","
            << topProduct->product.getQuantity() << std::endl;
  }

  // If replacing, save all products in the stack
  else if (mode == "replace")
  {
    ProductList::Node *temp = productList.getHead();
    while (temp != nullptr)
    {
      outFile << temp->product.getName() << ","
              << temp->product.getPrice() << ","
              << temp->product.getQuantity() << std::endl;
      temp = temp->next;
    }
  }

  outFile.close();
}

// Load all products from the file and push them onto the stack (one by one)
void Database::loadProducts(ProductList &productList)
{
  if (!std::filesystem::exists(sourceFile))
  {
    std::cerr << "File not found: " << sourceFile << std::endl;
    return;
  }

  std::ifstream inFile(sourceFile);
  if (!inFile)
  {
    std::cerr << "Unable to open file: " << sourceFile << std::endl;
    return;
  }

  std::string line;
  while (std::getline(inFile, line))
  {
    std::stringstream ss(line); // Parse the line
    std::string name;
    double price;
    int quantity;
    char delimiter;

    // Parse the product data
    std::getline(ss, name, ',');
    ss >> price >> delimiter >> quantity;

    // Add the parsed product to the stack
    Product newProduct(name, price, quantity);
    productList.pushProduct(newProduct); // Push to the stack
  }

  inFile.close();
}