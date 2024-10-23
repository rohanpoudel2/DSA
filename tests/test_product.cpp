#include <gtest/gtest.h>
#include "Product.h"
#include <sstream>

// Test default constructor
TEST(ProductTest, DefaultConstructor)
{
  Product product;

  // Check default values
  EXPECT_EQ(product.getName(), "___");
  EXPECT_EQ(product.getPrice(), 0.0);
  EXPECT_EQ(product.getQuantity(), 0.0);
}

// Test parameterized constructor
TEST(ProductTest, ParameterizedConstructor)
{
  Product product("Laptop", 1200.99, 5);

  // Check values after initialization
  EXPECT_EQ(product.getName(), "Laptop");
  EXPECT_EQ(product.getPrice(), 1200.99);
  EXPECT_EQ(product.getQuantity(), 5);
}

// Test setName and getName
TEST(ProductTest, SetAndGetName)
{
  Product product;
  product.setName("Keyboard");

  EXPECT_EQ(product.getName(), "Keyboard");
}

// Test setPrice and getPrice
TEST(ProductTest, SetAndGetPrice)
{
  Product product;
  product.setPrice(49.99);

  EXPECT_EQ(product.getPrice(), 49.99);
}

// Test setQuantity and getQuantity
TEST(ProductTest, SetAndGetQuantity)
{
  Product product;
  product.setQuantity(10);

  EXPECT_EQ(product.getQuantity(), 10);
}

// Test displayProduct
TEST(ProductTest, DisplayProduct)
{
  Product product("Monitor", 299.99, 3);
  std::stringstream buffer;

  // Redirect cout to buffer
  std::streambuf *oldCoutBuffer = std::cout.rdbuf(buffer.rdbuf());

  // Call displayProduct
  product.displayProduct();

  // Restore cout
  std::cout.rdbuf(oldCoutBuffer);

  // Verify the output
  std::string output = buffer.str();
  EXPECT_NE(output.find("Product Name: Monitor"), std::string::npos);
  EXPECT_NE(output.find("Price: $299.99"), std::string::npos);
  EXPECT_NE(output.find("Quantity: 3"), std::string::npos);
}