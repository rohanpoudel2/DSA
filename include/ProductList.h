#ifndef PRODUCTLIST_H
#define PRODUCTLIST_H

#include "Product.h"

class ProductList
{
public:
  // A structure to represent a node in the linked list
  struct Node
  {
    Product product; // The product stored in this node
    Node *next;      // Pointer to the next node in the list
  };

private:
  Node *head; // Pointer to the first node in the linked list (head of the list)

public:
  // Default constructor
  // Precondition: None
  // Postcondition: Initializes an empty list with head set to nullptr
  ProductList();

  // Destructor
  // Precondition: None
  // Postcondition: Frees the memory allocated for the nodes in the linked list
  ~ProductList();

  // Getter for the head of the list
  // Precondition: None
  // Postcondition: Returns a pointer to the first node (head) in the list
  Node *getHead() const;

  // Adds a product to the end of the linked list
  // Precondition: newProduct is a valid Product object
  // Postcondition: Adds a new node with the product at the end of the list
  void addProduct(const Product &newProduct);

  // Displays all the products in the linked list
  // Precondition: None
  // Postcondition: Prints each product in the list to standard output
  void displayAllProducts() const;
};

#endif