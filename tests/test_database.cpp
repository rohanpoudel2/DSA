#include <gtest/gtest.h>
#include "Database.h"
#include "ProductList.h"
#include "Product.h"

// Cleans the database by saving an empty ProductList
bool cleanDatabase(const std::string &filePath)
{
  Database db(filePath);
  ProductList emptyProductList;

  // Save an empty product list to clear the file
  db.saveProducts(emptyProductList, "replace");

  // Reload the product list to verify that it's empty
  db.loadProducts(emptyProductList);
  return emptyProductList.getHead() == nullptr;
}

// Test saving products to a text file
// Test saving products to a text file
TEST(DatabaseTest, SaveProductsToFile)
{
  const std::string filePath = "./data/test_products.txt";

  // Ensure the database is clean before starting the test
  ASSERT_TRUE(cleanDatabase(filePath));

  ProductList productList;
  ProductList newProductList;

  // Add products to the list (LIFO order)
  productList.pushProduct(Product("Mouse", 25.99, 15));
  productList.pushProduct(Product("Keyboard", 49.99, 10));

  // Save the product stack to the database file
  Database db(filePath);
  db.saveProducts(productList, "replace");

  // Load the products into a new list (after writing to file)
  db.loadProducts(newProductList);

  // Debugging: Print all products in the original and loaded lists
  std::cout << "Original product list:" << std::endl;
  ProductList::Node *productNode = productList.getHead();
  while (productNode != nullptr)
  {
    std::cout << productNode->product.getName() << std::endl;
    productNode = productNode->next;
  }

  std::cout << "Loaded product list:" << std::endl;
  ProductList::Node *newProductNode = newProductList.getHead();
  while (newProductNode != nullptr)
  {
    std::cout << newProductNode->product.getName() << std::endl;
    newProductNode = newProductNode->next;
  }

  // Reset pointers for comparison
  productNode = productList.getHead();
  newProductNode = newProductList.getHead();

  // **Important change here**: Reverse the original list order for comparison
  std::stack<ProductList::Node *> reverseStack;
  while (productNode != nullptr)
  {
    reverseStack.push(productNode);
    productNode = productNode->next;
  }

  // Now compare the reversed order of original products with the loaded products
  while (!reverseStack.empty() && newProductNode != nullptr)
  {
    ProductList::Node *reversedProductNode = reverseStack.top();
    reverseStack.pop();

    EXPECT_EQ(reversedProductNode->product.getName(), newProductNode->product.getName());
    EXPECT_EQ(reversedProductNode->product.getPrice(), newProductNode->product.getPrice());
    EXPECT_EQ(reversedProductNode->product.getQuantity(), newProductNode->product.getQuantity());

    newProductNode = newProductNode->next;
  }

  // Ensure both lists have the same length
  EXPECT_EQ(reverseStack.empty(), true);
  EXPECT_EQ(newProductNode, nullptr);
}

// Test undoing the last added product and saving the stack to the file
TEST(DatabaseTest, UndoLastAddedProduct)
{
  const std::string filePath = "./data/test_products.txt";

  // Ensure the database is clean before starting the test
  ASSERT_TRUE(cleanDatabase(filePath));

  ProductList productList;

  // Add products to the stack
  productList.pushProduct(Product("Mouse", 25.99, 15));
  productList.pushProduct(Product("Keyboard", 49.99, 10));

  // Save the stack to the file
  Database db(filePath);
  db.saveProducts(productList);

  // Undo the last added product (Keyboard) from the stack
  productList.popProduct();

  // After the undo operation, save the remaining products back to the database
  db.saveProducts(productList, "replace");

  // Reload the file to verify that "Keyboard" was removed
  ProductList newProductList;
  db.loadProducts(newProductList);

  ProductList::Node *productNode = newProductList.getHead();
  ASSERT_NE(productNode, nullptr);
  EXPECT_EQ(productNode->product.getName(), "Mouse");
  EXPECT_EQ(productNode->next, nullptr); // Only one product should remain
}