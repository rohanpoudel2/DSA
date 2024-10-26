#include <iostream>
#include "InquiryQueue.h"
#include "CustomQueue.h"

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
  if (queue.isEmpty())
  {
    std::cout << "No inquiries available.\n";
    return;
  }

  CustomQueue tempQueue = queue;

  while (!tempQueue.isEmpty())
  {
    Inquiry inquiry = tempQueue.peek();
    std::cout << "Customer Name: " << inquiry.getUser().getName() << "\n";
    std::cout << "Customer Email: " << inquiry.getUser().getEmail() << "\n";
    std::cout << "Inquiry Message: " << inquiry.getMessage() << "\n";
    std::cout << "Inquiry Response: " << inquiry.getResponse() << "\n";
    std::cout << "-------------------------------\n";

    // Dequeue each inquiry to avoid infinite loop
    tempQueue.dequeue();
  }
}

// Written by Rohan Poudel
bool InquiryQueue::isEmpty() const
{
  return queue.isEmpty();
}