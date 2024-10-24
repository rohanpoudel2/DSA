#include <iostream>

#include "InquiryQueue.h"

// Written by Rohan Poudel
InquiryQueue::InquiryQueue() {}

// Written by Rohan Poudel
void InquiryQueue::enqueue(const Inquiry &inquiry)
{
  queue.enqueue(inquiry);
}

// Written by Rohan Poudel
Inquiry InquiryQueue::dequeue()
{
  if (isEmpty())
  {
    throw std::runtime_error("No inquiries to dequeue.");
  }
  return queue.dequeue();
}

// Written by Rohan Poudel
Inquiry InquiryQueue::peekFront() const
{
  if (isEmpty())
  {
    throw std::runtime_error("No inquiries available.");
  }
  return queue.peek();
}

// Written by Rohan Poudel
void InquiryQueue::displayAllInquiries() const
{
  CustomQueue<Inquiry> tempQueue = queue; // Copy the queue

  if (tempQueue.isEmpty())
  {
    std::cout << "No inquiries available.\n";
    return;
  }

  while (!tempQueue.isEmpty())
  {
    Inquiry inquiry = tempQueue.dequeue();
    std::cout << "Customer Name: " << inquiry.getUser().getName() << "\n";
    std::cout << "Customer Email: " << inquiry.getUser().getEmail() << "\n";
    std::cout << "Inquiry Message: " << inquiry.getMessage() << "\n";
    std::cout << "Inquiry Response: " << inquiry.getResponse() << "\n";
    std::cout << "-------------------------------\n";
  }
}

// Written by Rohan Poudel
bool InquiryQueue::isEmpty() const
{
  return queue.isEmpty();
}