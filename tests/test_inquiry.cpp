#include <gtest/gtest.h>
#include "Inquiry.h"
#include "User.h"

// Test default constructor and initial values of Inquiry
TEST(InquiryTest, ConstructorAndGetters)
{
  // Create a User object to use in the Inquiry
  User user("John Doe", "johndoe@example.com", "customer", "password123");

  // Create an Inquiry object
  Inquiry inquiry(user, "How do I reset my password?", "Please follow the reset link.", "2023-10-20 12:34:56");

  // Verify that the getter methods return the correct values
  EXPECT_EQ(inquiry.getUser().getName(), "John Doe");
  EXPECT_EQ(inquiry.getUser().getEmail(), "johndoe@example.com");
  EXPECT_EQ(inquiry.getMessage(), "How do I reset my password?");
  EXPECT_EQ(inquiry.getResponse(), "Please follow the reset link.");
  EXPECT_EQ(inquiry.getTimestamp(), "2023-10-20 12:34:56");
}

// Test setters and modification of Inquiry properties
TEST(InquiryTest, Setters)
{
  // Create a User object
  User user("John Doe", "johndoe@example.com", "customer", "password123");

  // Create an Inquiry object
  Inquiry inquiry(user, "Initial message", "Initial response", "2023-10-20 12:00:00");

  // Modify the inquiry using the setter methods
  User newUser("Jane Smith", "janesmith@example.com", "customer", "password456");
  inquiry.setUser(newUser);
  inquiry.setMessage("How do I track my order?");
  inquiry.setResponse("You can track your order using the tracking number.");
  inquiry.setTimestamp("2023-10-21 14:20:00");
  inquiry.setInquiryId(101);

  // Verify that the values have been updated
  EXPECT_EQ(inquiry.getInquiryId(), 101);
  EXPECT_EQ(inquiry.getUser().getName(), "Jane Smith");
  EXPECT_EQ(inquiry.getUser().getEmail(), "janesmith@example.com");
  EXPECT_EQ(inquiry.getMessage(), "How do I track my order?");
  EXPECT_EQ(inquiry.getResponse(), "You can track your order using the tracking number.");
  EXPECT_EQ(inquiry.getTimestamp(), "2023-10-21 14:20:00");
}