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
void ProductList::addProduct(const Product &newProduct)
{
  Node *newNode = new Node{newProduct, nullptr}; // Create a new node with the product
  if (head == nullptr)                           // If the list is empty
  {
    head = newNode;
  }
  else
  {
    Node *temp = head;
    // Traverse to the end of the list
    while (temp->next != nullptr)
    {
      temp = temp->next;
    }
    temp->next = newNode; // Append the new node
  }
}

// Written by Rohan Poudel
void ProductList::displayAllProducts() const
{
  Node *current = head;
  while (current != nullptr)
  {
    current->product.displayProduct();
    current = current->next;
  }
}