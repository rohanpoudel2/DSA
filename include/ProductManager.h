#ifndef PRODUCT_MANAGER_H
#define PRODUCT_MANAGER_H

#include "Database.h"
#include "ProductList.h"

class ProductManager : public Database
{
public:
  ProductManager(const std::string &filename);
  void createTables() override;

  // Product-specific operations
  void saveProducts(const ProductList &productList, const std::string &mode = "append");
  void loadProducts(ProductList &productList);
};

#endif