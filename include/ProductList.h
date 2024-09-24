#ifndef PRODUCTLIST_H
#define PRODUCTLIST_H

#include "Product.h"

class ProductList
{
public:
  struct Node
  {
    Product product;
    Node *next;
  };

private:
  Node *head;

public:
  ProductList();
  ~ProductList();
  Node *getHead() const;

  void addProduct(const Product &newProduct);
  void displayAllProducts() const;
};

#endif