#include "Product.h"
#include <iostream>

Product::Product() : name("Unknown"), price(0.0), quantity(0.0) {}

Product::Product(std::string productName, double productPrice, double productQuantity)
    : name(productName), price(productPrice), quantity(productQuantity) {}

std::string Product::getName() const
{
  return name;
}

void Product::setName(std::string productName)
{
  name = productName;
}

double Product::getPrice() const
{
  return price;
}

void Product::setPrice(double productPrice)
{
  price = productPrice;
}

double Product::getQuantity() const
{
  return quantity;
}

void Product::setQuantity(double productQuantity)
{
  quantity = productQuantity;
}

void Product::displayProduct() const
{
  std::cout << "Product Name: " << name << std::endl;
  std::cout << "Price: $" << price << std::endl;
  std::cout << "Quantity: " << quantity << std::endl;
}