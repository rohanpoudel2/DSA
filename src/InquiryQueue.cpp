#include "InquiryQueue.h"
#include <iostream>

InquiryQueue::InquiryQueue() {}

void InquiryQueue::enqueue(const Inquiry &inquiry)
{
  queue.push(inquiry);
}

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

Inquiry InquiryQueue::peekFront() const
{
  if (isEmpty())
  {
    throw std::runtime_error("No inquiries available.");
  }
  return queue.front();
}

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
    std::cout << "-------------------------------\n";
    tempQueue.pop();
  }
}

bool InquiryQueue::isEmpty() const
{
  return queue.empty();
}