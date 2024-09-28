#include "Product.h"
#include <iostream>

//  Written by Rohan Poudel
Product::Product() : name("___"), price(0.0), quantity(0.0) {}

// Written by Rohan Poudel
Product::Product(std::string productName, double productPrice, double productQuantity)
    : name(productName), price(productPrice), quantity(productQuantity) {}

// Written by Rohan Poudel
std::string Product::getName() const
{
  return name;
}

// Written by Rohan Poudel
void Product::setName(std::string productName)
{
  name = productName;
}

// Written by Rohan Poudel
double Product::getPrice() const
{
  return price;
}

// Written by Rohan Poudel
void Product::setPrice(double productPrice)
{
  price = productPrice;
}

// Written by Rohan Poudel
double Product::getQuantity() const
{
  return quantity;
}

// Written by Rohan Poudel
void Product::setQuantity(double productQuantity)
{
  quantity = productQuantity;
}

// Written by Rohan Poudel
void Product::displayProduct() const
{
  using namespace std;
  cout << "Product Name: " << name << endl;
  cout << "Price: $" << price << endl;
  cout << "Quantity: " << quantity << endl;
}