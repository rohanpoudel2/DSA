#include <gtest/gtest.h>
#include "Product.h"

// Test the default constructor
TEST(ProductTest, DefaultConstructor)
{
  Product p;
  EXPECT_EQ(p.getName(), "___");
  EXPECT_EQ(p.getPrice(), 0.0);
  EXPECT_EQ(p.getQuantity(), 0.0);
}

// Test the parameterized constructor
TEST(ProductTest, ParameterizedConstructor)
{
  Product p("Laptop", 999.99, 10);
  EXPECT_EQ(p.getName(), "Laptop");
  EXPECT_EQ(p.getPrice(), 999.99);
  EXPECT_EQ(p.getQuantity(), 10);
}

// Test the setters and getters
TEST(ProductTest, SettersAndGetters)
{
  Product p;
  p.setName("Phone");
  p.setPrice(599.99);
  p.setQuantity(5);

  EXPECT_EQ(p.getName(), "Phone");
  EXPECT_EQ(p.getPrice(), 599.99);
  EXPECT_EQ(p.getQuantity(), 5);
}

// Test displayProduct (capture output)
TEST(ProductTest, DisplayProduct)
{
  Product product("Tablet", 299.99, 5);
  testing::internal::CaptureStdout(); // Capture console output
  product.displayProduct();
  std::string output = testing::internal::GetCapturedStdout();
  EXPECT_EQ(output, "Product Name: Tablet\nPrice: $299.99\nQuantity: 5\n");
}