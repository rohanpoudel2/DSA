#include "ProductList.h"
#include <iostream>

// Written by Rohan Poudel
ProductList::ProductList() : head(nullptr) {}

// Written by Rohan Poudel
ProductList::~ProductList()
{
  Node *current = head;
  while (current != nullptr)
  {
    Node *temp = current;
    current = current->next;
    delete temp; // Deallocate memory for each node
  }
}

// Written by Rohan Poudel
ProductList::Node *ProductList::getHead() const
{
  return head;
}

// Written by Rohan Poudel
void ProductList::pushProduct(const Product &newProduct)
{
  Node *newNode = new Node{newProduct, nullptr};
  newNode->next = head;
  head = newNode;
}

// Written by Rohan Poudel
Product ProductList::popProduct()
{
  if (head == nullptr)
  {
    std::cerr << "No products to pop!" << std::endl;
    return Product(); // Return a default-constructed Product
  }
  Node *temp = head;
  Product poppedProduct = head->product;
  head = head->next;
  delete temp;

  return poppedProduct;
}

// Written by Rohan Poudel
void ProductList::displayAllProducts() const
{
  Node *current = head;
  if (current == nullptr)
  {
    std::cout << "No products to display!" << std::endl;
    return;
  }
  while (current != nullptr)
  {
    current->product.displayProduct();
    current = current->next;
  }
}

// Written by Rohan Poudel
void ProductList::clear()
{
  while (head != nullptr)
  {
    Node *temp = head;
    head = head->next;
    delete temp;
  }
  head = nullptr;
}

// Written by Rohan Poudel
bool ProductList::isEmpty() const
{
  return head == nullptr;
}