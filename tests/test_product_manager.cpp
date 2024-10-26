#include <gtest/gtest.h>
#include "ProductManager.h"
#include "ProductList.h"
#include "Product.h"
#include "Utils.h"
#include "Environment.h"

// Helper function to clean the database by clearing the products table
void clearProductsTable(ProductManager &productManager)
{
  ProductList emptyProductList;
  productManager.saveProducts(emptyProductList, "replace");
}

// Test creating the products table
TEST(ProductManagerTest, CreateTable)
{
  ProductManager productManager(Utils::getDatabasePath(Environment::environment));

  // Check if the table was created by executing a SELECT query
  sqlite3_stmt *stmt;
  const char *sqlCheck = "SELECT name FROM sqlite_master WHERE type='table' AND name='products';";
  sqlite3_prepare_v2(productManager.getDB(), sqlCheck, -1, &stmt, nullptr);

  // If there is at least one row returned, the table exists
  int step = sqlite3_step(stmt);
  EXPECT_EQ(step, SQLITE_ROW); // Table should exist

  sqlite3_finalize(stmt);
}

// Test saving products to the database
TEST(ProductManagerTest, SaveProducts)
{
  ProductManager productManager(Utils::getDatabasePath(Environment::environment));
  ProductList productList;

  // Clear the products table before starting the test
  clearProductsTable(productManager);

  // Add some products to the list
  productList.pushProduct(Product("Laptop", 999.99, 5));
  productList.pushProduct(Product("Headphones", 199.99, 10));

  // Save the products to the database
  productManager.saveProducts(productList, "replace");

  // Verify the products were saved by loading them into a new list
  ProductList loadedProductList;
  productManager.loadProducts(loadedProductList);

  // Compare the loaded products with the original products
  ProductList::Node *originalNode = productList.getHead();
  ProductList::Node *loadedNode = loadedProductList.getHead();

  while (originalNode != nullptr && loadedNode != nullptr)
  {
    EXPECT_EQ(originalNode->product.getName(), loadedNode->product.getName());
    EXPECT_EQ(originalNode->product.getPrice(), loadedNode->product.getPrice());
    EXPECT_EQ(originalNode->product.getQuantity(), loadedNode->product.getQuantity());

    originalNode = originalNode->next;
    loadedNode = loadedNode->next;
  }

  // Ensure both lists have the same number of products
  EXPECT_EQ(originalNode, nullptr);
  EXPECT_EQ(loadedNode, nullptr);
}

// Test loading products from the database
TEST(ProductManagerTest, LoadProducts)
{
  ProductManager productManager(Utils::getDatabasePath(Environment::environment));
  ProductList productList;

  // Clear the products table before starting the test
  clearProductsTable(productManager);

  // Add some products to the list and save them to the database
  productList.pushProduct(Product("Keyboard", 49.99, 20));
  productList.pushProduct(Product("Mouse", 29.99, 30));
  productManager.saveProducts(productList, "replace");

  // Load products from the database into a new list
  ProductList loadedProductList;
  productManager.loadProducts(loadedProductList);

  // Verify the loaded products match the saved products
  ProductList::Node *originalNode = productList.getHead();
  ProductList::Node *loadedNode = loadedProductList.getHead();

  while (originalNode != nullptr && loadedNode != nullptr)
  {
    EXPECT_EQ(originalNode->product.getName(), loadedNode->product.getName());
    EXPECT_EQ(originalNode->product.getPrice(), loadedNode->product.getPrice());
    EXPECT_EQ(originalNode->product.getQuantity(), loadedNode->product.getQuantity());

    originalNode = originalNode->next;
    loadedNode = loadedNode->next;
  }

  // Ensure both lists have the same number of products
  EXPECT_EQ(originalNode, nullptr);
  EXPECT_EQ(loadedNode, nullptr);
}

// Test replacing products in the database
TEST(ProductManagerTest, ReplaceProducts)
{
  ProductManager productManager(Utils::getDatabasePath(Environment::environment));
  ProductList productList;

  // Clear the products table before starting the test
  clearProductsTable(productManager);

  // Add some products to the list and save them to the database
  productList.pushProduct(Product("Tablet", 499.99, 8));
  productManager.saveProducts(productList, "replace");

  // Verify the product was saved
  ProductList loadedProductList;
  productManager.loadProducts(loadedProductList);

  ProductList::Node *loadedNode = loadedProductList.getHead();
  ASSERT_NE(loadedNode, nullptr);
  EXPECT_EQ(loadedNode->product.getName(), "Tablet");
  EXPECT_EQ(loadedNode->product.getPrice(), 499.99);
  EXPECT_EQ(loadedNode->product.getQuantity(), 8);

  // Now replace with new products
  ProductList newProductList;
  newProductList.pushProduct(Product("Smartphone", 899.99, 15));
  productManager.saveProducts(newProductList, "replace");

  // Verify the products were replaced
  ProductList newLoadedProductList;
  productManager.loadProducts(newLoadedProductList);

  ProductList::Node *newLoadedNode = newLoadedProductList.getHead();
  ASSERT_NE(newLoadedNode, nullptr);
  EXPECT_EQ(newLoadedNode->product.getName(), "Smartphone");
  EXPECT_EQ(newLoadedNode->product.getPrice(), 899.99);
  EXPECT_EQ(newLoadedNode->product.getQuantity(), 15);
  EXPECT_EQ(newLoadedNode->next, nullptr); // Only one product should exist after replace
}