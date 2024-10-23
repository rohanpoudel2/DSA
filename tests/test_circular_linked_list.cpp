#include <gtest/gtest.h>
#include "CircularLinkedList.h"

// Test that a newly created CircularLinkedList is empty
TEST(CircularLinkedListTest, IsEmptyInitially)
{
  CircularLinkedList list;
  EXPECT_TRUE(list.isEmpty());
}

// Test adding a discount to the list
TEST(CircularLinkedListTest, AddSingleDiscount)
{
  CircularLinkedList list;
  list.addDiscount(10);

  EXPECT_FALSE(list.isEmpty());
}

// Test adding multiple discounts to the list
TEST(CircularLinkedListTest, AddMultipleDiscounts)
{
  CircularLinkedList list;
  list.addDiscount(5);
  list.addDiscount(10);
  list.addDiscount(15);

  EXPECT_FALSE(list.isEmpty());
}

// Test spinning the wheel when the list is empty
TEST(CircularLinkedListTest, SpinWheelEmptyList)
{
  CircularLinkedList list;
  int result = list.spinWheel();
  EXPECT_EQ(result, 0); // Expect 0 when spinning with an empty list
}

// Test spinning the wheel with one item in the list
TEST(CircularLinkedListTest, SpinWheelWithSingleDiscount)
{
  CircularLinkedList list;
  list.addDiscount(20);

  // Spin the wheel and check if the single discount is returned
  int result = list.spinWheel();
  EXPECT_EQ(result, 20);
}

// Test spinning the wheel with multiple items in the list
TEST(CircularLinkedListTest, SpinWheelWithMultipleDiscounts)
{
  CircularLinkedList list;
  list.addDiscount(5);
  list.addDiscount(10);
  list.addDiscount(15);
  list.addDiscount(20);

  // Spin the wheel multiple times to ensure valid results
  for (int i = 0; i < 10; ++i)
  {
    int result = list.spinWheel();
    EXPECT_TRUE(result == 5 || result == 10 || result == 15 || result == 20);
  }
}

// Test that the destructor properly frees the nodes in the list
TEST(CircularLinkedListTest, DestructorTest)
{
  CircularLinkedList *list = new CircularLinkedList();
  list->addDiscount(5);
  list->addDiscount(10);
  delete list; // After deletion, ensure no memory leaks or crashes

  // If the test completes without a crash or memory leak, it's considered passed
  SUCCEED();
}