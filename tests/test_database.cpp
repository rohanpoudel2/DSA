#include <gtest/gtest.h>
#include <fstream>
#include <iostream>
#include "Database.h"
#include "ProductList.h"
#include "Product.h"

// Cleans the specified database by saving an empty ProductList
bool cleanDatabase(const std::string &filePath)
{
  Database db(filePath);
  ProductList emptyProductList;

  // Save an empty product list to clear the file
  db.saveProducts(emptyProductList, "Replace");

  // Reload the product list to verify that it's empty
  db.loadProducts(emptyProductList);
  return emptyProductList.getHead() == nullptr;
}

// Test saving products to a text file
TEST(DatabaseTest, SaveProductsToFile)
{
  const std::string filePath = "./data/test_products.txt";

  // Ensure the database is clean before starting the test
  ASSERT_TRUE(cleanDatabase(filePath));

  ProductList productList;
  ProductList newProductList;

  // Add products to the list
  productList.addProduct(Product("Mouse", 25.99, 15));
  productList.addProduct(Product("Keyboard", 49.99, 10));

  // Create a Database object and save the products
  Database db(filePath);
  db.saveProducts(productList);

  // Load the products into a new list
  db.loadProducts(newProductList);

  // Verify that the saved and loaded products match
  ProductList::Node *productNode = productList.getHead();
  ProductList::Node *newProductNode = newProductList.getHead();

  while (productNode != nullptr && newProductNode != nullptr)
  {
    EXPECT_EQ(productNode->product.getName(), newProductNode->product.getName());
    EXPECT_EQ(productNode->product.getPrice(), newProductNode->product.getPrice());
    EXPECT_EQ(productNode->product.getQuantity(), newProductNode->product.getQuantity());

    productNode = productNode->next;
    newProductNode = newProductNode->next;
  }

  // Ensure both lists have the same length
  EXPECT_EQ(productNode, nullptr);
  EXPECT_EQ(newProductNode, nullptr);
}

// Test loading products from a text file
TEST(DatabaseTest, LoadProductsFromFile)
{
  const std::string filePath = "./data/test_products.txt";

  // Ensure the database is clean before starting the test
  ASSERT_TRUE(cleanDatabase(filePath));

  // Initialize products to be added to the list
  std::array<Product, 2> products = {
      Product("Laptop", 123.2, 12),
      Product("Monitor", 1123.2, 102)};

  ProductList productList;
  Database db(filePath);

  // Add products to the list
  for (const auto &product : products)
  {
    productList.addProduct(product);
  }

  // Save the product list to the database
  db.saveProducts(productList);

  // Reinitialize the product list
  productList = ProductList();

  // Load the products from the database
  db.loadProducts(productList);

  // Verify the loaded products match the original products
  ProductList::Node *current = productList.getHead();
  for (int i = 0; i < products.size(); i++)
  {
    // Checking if there is a node
    ASSERT_NE(current, nullptr);
    EXPECT_EQ(current->product.getName(), products[i].getName());
    EXPECT_EQ(current->product.getPrice(), products[i].getPrice());
    EXPECT_EQ(current->product.getQuantity(), products[i].getQuantity());
    // Moving to the next node
    current = current->next;
  }
  // Checking to see no more nodes are present
  EXPECT_EQ(current, nullptr);
}