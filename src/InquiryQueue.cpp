#include "InquiryQueue.h"
#include <iostream>

// Written by Rohan Poudel
InquiryQueue::InquiryQueue() {}

// Written by Rohan Poudel
void InquiryQueue::enqueue(const Inquiry &inquiry)
{
  queue.push(inquiry);
}

// Written by Rohan Poudel
Inquiry InquiryQueue::dequeue()
{
  if (isEmpty())
  {
    throw std::runtime_error("No inquiries to dequeue.");
  }
  Inquiry inquiry = queue.front();
  queue.pop();
  return inquiry;
}

// Written by Rohan Poudel
Inquiry InquiryQueue::peekFront() const
{
  if (isEmpty())
  {
    throw std::runtime_error("No inquiries available.");
  }
  return queue.front();
}

// Written by Rohan Poudel
void InquiryQueue::displayAllInquiries() const
{
  std::queue<Inquiry> tempQueue = queue;

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
    std::cout << "Inquiry Response: " << inquiry.getResponse() << "\n";
    std::cout << "-------------------------------\n";
    tempQueue.pop();
  }
}

// Written by Rohan Poudel
bool InquiryQueue::isEmpty() const
{
  return queue.empty();
}