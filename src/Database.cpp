#include "Database.h"
#include <fstream>
#include <iostream>

Database::Database(const std::string &filename) : source(filename) {}

Database::~Database() {}

void Database::loadProducts(ProductList &productList)
{
  loadFromTextFile(productList);
}

void Database::saveProducts(const ProductList &productList)
{
  saveToTextFile(productList);
}

void Database::loadFromTextFile(ProductList &productList)
{
  std::ifstream inFile(source);
  if (!inFile)
  {
    std::ofstream createFile(source);
    if (!createFile)
    {
      std::cerr << "Unable to create file: " << source << std::endl;
      return;
    }
    createFile.close();
    inFile.open(source);
    if (!inFile)
    {
      std::cerr << "Unable to open file: " << source << std::endl;
      return;
    }
  }
  std::string name;
  double price;
  int quantity;

  while (inFile >> name >> price >> quantity)
  {
    Product newProduct(name, price, quantity);
    productList.addProduct(newProduct);
  }

  inFile.close();
}

void Database::saveToTextFile(const ProductList &productList)
{
  std::ofstream outFile(source);
  if (!outFile)
  {
    std::cerr << "Unable to open file: " << source << std::endl;
    return;
  }
  ProductList::Node *temp = productList.getHead();
  while (temp != nullptr)
  {
    outFile << temp->product.getName() << ","
            << temp->product.getPrice() << ","
            << temp->product.getQuantity() << std::endl;
    temp = temp->next;
  }

  outFile.close();
}