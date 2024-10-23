#include <gtest/gtest.h>
#include "InquiryQueue.h"
#include "User.h"
#include "Inquiry.h"

// Test enqueue and dequeue operations in InquiryQueue
TEST(InquiryQueueTest, EnqueueAndDequeue)
{
  // Create a User and Inquiry objects
  User user("John Doe", "johndoe@example.com", "customer", "password123");
  Inquiry inquiry1(user, "How do I reset my password?", "Please follow the reset link.", "2023-10-20 12:34:56");
  Inquiry inquiry2(user, "Where is my order?", "It's on the way.", "2023-10-21 14:20:00");

  // Create an InquiryQueue and enqueue two inquiries
  InquiryQueue inquiryQueue;
  inquiryQueue.enqueue(inquiry1);
  inquiryQueue.enqueue(inquiry2);

  // Check that the queue is not empty
  EXPECT_FALSE(inquiryQueue.isEmpty());

  // Dequeue the first inquiry and verify its details
  Inquiry dequeuedInquiry = inquiryQueue.dequeue();
  EXPECT_EQ(dequeuedInquiry.getMessage(), "How do I reset my password?");
  EXPECT_EQ(dequeuedInquiry.getResponse(), "Please follow the reset link.");
  EXPECT_EQ(dequeuedInquiry.getTimestamp(), "2023-10-20 12:34:56");

  // Dequeue the second inquiry and verify its details
  dequeuedInquiry = inquiryQueue.dequeue();
  EXPECT_EQ(dequeuedInquiry.getMessage(), "Where is my order?");
  EXPECT_EQ(dequeuedInquiry.getResponse(), "It's on the way.");
  EXPECT_EQ(dequeuedInquiry.getTimestamp(), "2023-10-21 14:20:00");

  // Check that the queue is now empty
  EXPECT_TRUE(inquiryQueue.isEmpty());
}

// Test peekFront method to ensure it shows the correct inquiry without removing it
TEST(InquiryQueueTest, PeekFront)
{
  // Create a User and an Inquiry object
  User user("Jane Smith", "janesmith@example.com", "customer", "password456");
  Inquiry inquiry(user, "What is the return policy?", "", "2023-10-22 09:00:00");

  // Create an InquiryQueue and enqueue the inquiry
  InquiryQueue inquiryQueue;
  inquiryQueue.enqueue(inquiry);

  // Peek at the front inquiry and verify the details without removing it
  Inquiry peekedInquiry = inquiryQueue.peekFront();
  EXPECT_EQ(peekedInquiry.getMessage(), "What is the return policy?");
  EXPECT_EQ(peekedInquiry.getResponse(), "");
  EXPECT_EQ(peekedInquiry.getTimestamp(), "2023-10-22 09:00:00");

  // Verify that the queue is not empty after peeking
  EXPECT_FALSE(inquiryQueue.isEmpty());
}

// Test the behavior of InquiryQueue when dequeue is called on an empty queue
TEST(InquiryQueueTest, DequeueEmptyQueue)
{
  InquiryQueue inquiryQueue;

  // Check that the queue is initially empty
  EXPECT_TRUE(inquiryQueue.isEmpty());

  // Try to dequeue from an empty queue and expect an exception
  EXPECT_THROW(inquiryQueue.dequeue(), std::runtime_error);
}

// Test displayAllInquiries method to ensure it outputs the correct inquiries
TEST(InquiryQueueTest, DisplayAllInquiries)
{
  // Create User and Inquiry objects
  User user("Alice Johnson", "alicejohnson@example.com", "customer", "password789");
  Inquiry inquiry1(user, "How do I cancel my order?", "", "2023-10-23 10:45:00");
  Inquiry inquiry2(user, "Can I change my shipping address?", "", "2023-10-23 11:00:00");

  // Create an InquiryQueue and enqueue inquiries
  InquiryQueue inquiryQueue;
  inquiryQueue.enqueue(inquiry1);
  inquiryQueue.enqueue(inquiry2);

  // Redirect std::cout to capture the output
  testing::internal::CaptureStdout();
  inquiryQueue.displayAllInquiries();
  std::string output = testing::internal::GetCapturedStdout();

  // Verify that the output contains the correct inquiry details
  EXPECT_NE(output.find("How do I cancel my order?"), std::string::npos);
  EXPECT_NE(output.find("Can I change my shipping address?"), std::string::npos);
  EXPECT_NE(output.find("alicejohnson@example.com"), std::string::npos);
}

// Test isEmpty method to ensure it correctly identifies an empty queue
TEST(InquiryQueueTest, IsEmpty)
{
  InquiryQueue inquiryQueue;

  // Initially the queue should be empty
  EXPECT_TRUE(inquiryQueue.isEmpty());

  // Add an inquiry to the queue
  User user("John Doe", "johndoe@example.com", "customer", "password123");
  Inquiry inquiry(user, "How do I reset my password?", "", "2023-10-24 09:30:00");
  inquiryQueue.enqueue(inquiry);

  // Now the queue should not be empty
  EXPECT_FALSE(inquiryQueue.isEmpty());

  // Dequeue the inquiry and check if the queue is empty again
  inquiryQueue.dequeue();
  EXPECT_TRUE(inquiryQueue.isEmpty());
}