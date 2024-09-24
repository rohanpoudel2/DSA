#include <gtest/gtest.h>
#include "ProductList.h"

// Test the addProduct method
TEST(ProductListTest, AddProduct)
{
  ProductList list;
  Product p("Phone", 599.99, 5);
  list.addProduct(p);

  // Check if the head of the list contains the product
  ProductList::Node *head = list.getHead();
  ASSERT_NE(head, nullptr);
  EXPECT_EQ(head->product.getName(), "Phone");
  EXPECT_EQ(head->product.getPrice(), 599.99);
  EXPECT_EQ(head->product.getQuantity(), 5);
}

// Test adding multiple products
TEST(ProductListTest, AddMultipleProducts)
{
  ProductList list;
  Product p1("Phone", 599.99, 5);
  Product p2("Laptop", 999.99, 3);

  list.addProduct(p1);
  list.addProduct(p2);

  ProductList::Node *head = list.getHead();
  ASSERT_NE(head, nullptr);
  EXPECT_EQ(head->product.getName(), "Phone");

  ProductList::Node *second = head->next;
  ASSERT_NE(second, nullptr);
  EXPECT_EQ(second->product.getName(), "Laptop");
}