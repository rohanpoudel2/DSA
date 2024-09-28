#include "Database.h"
#include <fstream>
#include <iostream>
#include <filesystem>

// Written by Rohan Poudel
Database::Database(const std::string &filename) : sourceFile(filename) {}

// Generated with AI assistance (ChatGPT)
// Saves the product list to the file, creating the file and directory if necessary
void Database::saveProducts(const ProductList &productList)
{
  // Create the directory path if it doesn't exist
  std::filesystem::path filePath(sourceFile);
  std::filesystem::create_directories(filePath.parent_path());

  // Open the file in append mode (creates the file if it doesn't exist)
  std::ofstream outFile(sourceFile, std::ios::app);
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