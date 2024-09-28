#include "Database.h"
#include <fstream>
#include <iostream>
#include <filesystem>
#include <string>
#include <sstream>

// Written by Rohan Poudel
Database::Database(const std::string &filename) : sourceFile(filename) {}

// Generated with AI assistance (ChatGPT)
// Saves the product list to the file, creating the file and directory if necessary
void Database::saveProducts(const ProductList &productList, const std::string &mode)
{
  // Create the directory path if it doesn't exist
  std::filesystem::path filePath(sourceFile);
  std::filesystem::create_directories(filePath.parent_path());

  // Open the file in append mode (creates the file if it doesn't exist)
  std::ofstream outFile(sourceFile, mode == "append" ? std::ios::app : std::ios::trunc);
  if (!outFile) // Error handling: Check if the file is successfully opened
  {
    std::cerr << "Unable to open file: " << sourceFile << std::endl;
    return;
  }

  // Get the head of the ProductList
  ProductList::Node *temp = productList.getHead();

  // Traverse the linked list and write each product to the file
  // Code refactored by AI (ChatGPT)
  while (temp != nullptr)
  {
    outFile << temp->product.getName() << ","  // Write product name
            << temp->product.getPrice() << "," // Write product price
            << temp->product.getQuantity()     // Write product quantity
            << std::endl;
    temp = temp->next; // Move to the next node in the list
  }

  // Close the file after writing
  outFile.close();
}

// Generated with AI assistance (ChatGPT)
// Load products from a text file into a ProductList
void Database::loadProducts(ProductList &productList)
{
  // Check if the file exists using std::filesystem
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
    std::stringstream ss(line); // Use stringstream to parse the line
    std::string name;
    double price;
    int quantity;
    char delimiter;

    // Parse the product details from the line (comma-separated values)
    std::getline(ss, name, ',');
    ss >> price >> delimiter >> quantity;

    // Add the parsed product to the product list
    Product newProduct(name, price, quantity);
    productList.addProduct(newProduct);
  }

  inFile.close();
}