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
  Product();
  Product(std::string productName, double productPrice, double productQuantity);

  std::string getName() const;
  void setName(std::string productName);

  double getPrice() const;
  void setPrice(double productPrice);

  double getQuantity() const;
  void setQuantity(double productQuantity);

  void displayProduct() const;
};

#endif