#include <gtest/gtest.h>
#include "ProductList.h"

// Test adding products to the list
TEST(ProductListTest, AddProduct)
{
  ProductList productList;

  Product product1("Phone", 499.99, 20);
  Product product2("Laptop", 999.99, 10);

  productList.addProduct(product1);
  productList.addProduct(product2);

  // Verify the first product in the list
  ASSERT_NE(productList.getHead(), nullptr);
  EXPECT_EQ(productList.getHead()->product.getName(), "Phone");

  // Verify the second product in the list
  ASSERT_NE(productList.getHead()->next, nullptr);
  EXPECT_EQ(productList.getHead()->next->product.getName(), "Laptop");
}