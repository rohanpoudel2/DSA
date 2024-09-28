#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

class Product
{
private:
  std::string name;
  double price;
  double quantity;

public:
  // Default constructor
  Product();

  // Parameterized constructor
  Product(std::string productName, double productPrice, double productQuantity);

  // Getter for the product name
  // Precondition: None
  // Postcondition: Returns the product name
  std::string getName() const;

  // Setter for the product name
  // Precondition: productName must be a valid string
  // Postcondition: Sets the product name
  void setName(std::string productName);

  // Getter for the product price
  // Precondition: None
  // Postcondition: Returns the product price
  double getPrice() const;

  // Setter for the product price
  // Precondition: productPrice must be non-negative
  // Postcondition: Sets the product price
  void setPrice(double productPrice);

  // Getter for the product quantity
  // Precondition: None
  // Postcondition: Returns the product quantity
  double getQuantity() const;

  // Setter for the product quantity
  // Precondition: productQuantity must be non-negative
  // Postcondition: Sets the product quantity
  void setQuantity(double productQuantity);

  // Displays the product's details
  // Precondition: None
  // Postcondition: Prints product details (name, price, quantity) to the console
  void displayProduct() const;
};

#endif