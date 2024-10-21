#include "InquiryQueue.h"
#include <iostream>

// Constructor initializes an empty queue
InquiryQueue::InquiryQueue() {}

// Enqueue a new inquiry
void InquiryQueue::enqueue(const Inquiry &inquiry)
{
  queue.push(inquiry);
}

// Dequeue the oldest inquiry (FIFO)
Inquiry InquiryQueue::dequeue()
{
  if (isEmpty())
  {
    throw std::runtime_error("No inquiries to dequeue.");
  }
  Inquiry inquiry = queue.front(); // Get the front inquiry
  queue.pop();                     // Remove it from the queue
  return inquiry;                  // Return the dequeued inquiry
}

// Peek the front inquiry without dequeuing
Inquiry InquiryQueue::peekFront() const
{
  if (isEmpty())
  {
    throw std::runtime_error("No inquiries available.");
  }
  return queue.front();
}

// Display all pending inquiries
void InquiryQueue::displayAllInquiries() const
{
  std::queue<Inquiry> tempQueue = queue; // Copy the queue to iterate through

  if (tempQueue.empty())
  {
    std::cout << "No inquiries available.\n";
    return;
  }

  while (!tempQueue.empty())
  {
    Inquiry inquiry = tempQueue.front();
    std::cout << "Customer Name: " << inquiry.getUser().getName() << "\n";
    std::cout << "Customer Email: " << inquiry.getUser().getEmail() << "\n";
    std::cout << "Inquiry Message: " << inquiry.getMessage() << "\n";
    std::cout << "-------------------------------\n";
    tempQueue.pop();
  }
}

// Check if the queue is empty
bool InquiryQueue::isEmpty() const
{
  return queue.empty();
}