#include <gtest/gtest.h>
#include "ProductList.h"
#include "Product.h"

// Test the constructor and isEmpty method
TEST(ProductListTest, DefaultConstructor)
{
  ProductList productList;
  EXPECT_TRUE(productList.isEmpty());
}

// Test pushing products onto the list
TEST(ProductListTest, PushProduct)
{
  ProductList productList;
  productList.pushProduct(Product("Laptop", 1000.0, 2));

  EXPECT_FALSE(productList.isEmpty());
  EXPECT_EQ(productList.getHead()->product.getName(), "Laptop");
  EXPECT_EQ(productList.getHead()->product.getPrice(), 1000.0);
  EXPECT_EQ(productList.getHead()->product.getQuantity(), 2);
}

// Test popping products from the list
TEST(ProductListTest, PopProduct)
{
  ProductList productList;
  productList.pushProduct(Product("Mouse", 25.99, 5));
  productList.pushProduct(Product("Keyboard", 49.99, 10));

  // Pop the last product added (LIFO order)
  Product poppedProduct = productList.popProduct();
  EXPECT_EQ(poppedProduct.getName(), "Keyboard");
  EXPECT_EQ(poppedProduct.getPrice(), 49.99);
  EXPECT_EQ(poppedProduct.getQuantity(), 10);

  // Now the head should be the "Mouse"
  EXPECT_EQ(productList.getHead()->product.getName(), "Mouse");

  // Pop the next product
  poppedProduct = productList.popProduct();
  EXPECT_EQ(poppedProduct.getName(), "Mouse");

  // The list should now be empty
  EXPECT_TRUE(productList.isEmpty());
}

// Test popping a product from an empty list
TEST(ProductListTest, PopProductFromEmptyList)
{
  ProductList productList;
  Product poppedProduct = productList.popProduct(); // Should return default-constructed product
  EXPECT_EQ(poppedProduct.getName(), "___");        // Default product name
  EXPECT_EQ(poppedProduct.getPrice(), 0.0);         // Default product price
  EXPECT_EQ(poppedProduct.getQuantity(), 0.0);      // Default product quantity
  EXPECT_TRUE(productList.isEmpty());
}

// Test displaying all products (checks output via cout)
TEST(ProductListTest, DisplayAllProducts)
{
  ProductList productList;
  productList.pushProduct(Product("Mouse", 25.99, 5));
  productList.pushProduct(Product("Keyboard", 49.99, 10));

  // Redirect std::cout to a stringstream
  std::stringstream buffer;
  std::streambuf *oldCout = std::cout.rdbuf(buffer.rdbuf());

  // Display all products
  productList.displayAllProducts();

  // Restore std::cout
  std::cout.rdbuf(oldCout);

  std::string output = buffer.str();
  EXPECT_NE(output.find("Product Name: Keyboard"), std::string::npos);
  EXPECT_NE(output.find("Product Name: Mouse"), std::string::npos);
}

// Test the clear method
TEST(ProductListTest, Clear)
{
  ProductList productList;
  productList.pushProduct(Product("Mouse", 25.99, 5));
  productList.pushProduct(Product("Keyboard", 49.99, 10));

  productList.clear();
  EXPECT_TRUE(productList.isEmpty());
}

// Test isEmpty method when list has products
TEST(ProductListTest, IsEmpty)
{
  ProductList productList;
  EXPECT_TRUE(productList.isEmpty());

  productList.pushProduct(Product("Mouse", 25.99, 5));
  EXPECT_FALSE(productList.isEmpty());
}