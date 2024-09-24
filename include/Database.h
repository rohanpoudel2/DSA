#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include "Product.h"
#include "ProductList.h"

class Database
{
public:
  Database(const std::string &filename);
  ~Database();

  void loadProducts(ProductList &productList);
  void saveProducts(const ProductList &productList);

private:
  std::string source;

  void loadFromTextFile(ProductList &productList);
  void saveToTextFile(const ProductList &productList);
};

#endif