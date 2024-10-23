#ifndef PRODUCT_MANAGER_H
#define PRODUCT_MANAGER_H

#include "Database.h"
#include "ProductList.h"

class ProductManager : public Database
{
public:
  // Constructor for ProductManager
  // Precondition: A valid database filename must be provided.
  // Postcondition: Initializes the ProductManager and connects to the specified database.
  ProductManager(const std::string &filename);

  // Creates the product table in the database.
  // Precondition: Database connection must be established.
  // Postcondition: The products table is created if it doesn't already exist.
  void createTable();

  // Saves products to the database.
  // Precondition: A valid ProductList and a mode ("append" or "replace") must be provided.
  // Postcondition: The products are either appended to or replace the existing products in the database.
  void saveProducts(const ProductList &productList, const std::string &mode = "append");

  // Loads products from the database.
  // Precondition: ProductList object must be passed to store the loaded products.
  // Postcondition: Populates the provided ProductList with data from the database.
  void loadProducts(ProductList &productList);
};

#endif