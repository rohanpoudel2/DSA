#include <gtest/gtest.h>
#include "ProductList.h"

// Test adding products to the stack
TEST(ProductListTest, AddProduct)
{
  ProductList productList;

  Product product1("Phone", 499.99, 20);
  Product product2("Laptop", 999.99, 10);

  productList.pushProduct(product1);
  productList.pushProduct(product2);

  // Verify the first product in the list which should be Laptop since it was added last
  ASSERT_NE(productList.getHead(), nullptr);
  EXPECT_EQ(productList.getHead()->product.getName(), "Laptop");

  // Verify the second product in the list
  ASSERT_NE(productList.getHead()->next, nullptr);
  EXPECT_EQ(productList.getHead()->next->product.getName(), "Phone");
}

// Test removing products from the stack
TEST(ProductListTest, RemoveProduct)
{
  ProductList productList;

  Product product1("Phone", 499.99, 20);
  Product product2("Laptop", 999.99, 10);

  productList.pushProduct(product1);
  productList.pushProduct(product2);

  // Remove the top product from the list
  Product poppedProduct = productList.popProduct();

  // Verify the removed product
  EXPECT_EQ(poppedProduct.getName(), "Laptop");

  // Verify the new top product in the list
  ASSERT_NE(productList.getHead(), nullptr);
  EXPECT_EQ(productList.getHead()->product.getName(), "Phone");
}