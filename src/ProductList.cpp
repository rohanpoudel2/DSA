#include "ProductList.h"
#include <iostream>

ProductList::ProductList() : head(nullptr) {}

ProductList::~ProductList()
{
  Node *current = head;
  while (current != nullptr)
  {
    Node *temp = current;
    current = current->next;
    delete temp;
  }
}

ProductList::Node *ProductList::getHead() const
{
  return head;
}

void ProductList::addProduct(const Product &newProduct)
{
  Node *newNode = new Node{newProduct, nullptr};
  if (head == nullptr)
  {
    head = newNode;
  }
  else
  {
    Node *temp = head;
    while (temp->next != nullptr)
    {
      temp = temp->next;
    }
    temp->next = newNode;
  }
}

void ProductList::displayAllProducts() const
{
  Node *temp = head;
  if (temp == nullptr)
  {
    std::cout << "No products in the store." << std::endl;
  }
  else
  {
    while (temp != nullptr)
    {
      temp->product.displayProduct();
      std::cout << "----------------------" << std::endl;
      temp = temp->next;
    }
  }
}