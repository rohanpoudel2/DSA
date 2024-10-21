#include "InquiryQueue.h"
#include <iostream>

// Constructor initializes front and rear to nullptr (empty queue)
InquiryQueue::InquiryQueue() : front(nullptr), rear(nullptr) {}

// Destructor deallocates all nodes
InquiryQueue::~InquiryQueue()
{
  while (front != nullptr)
  {
    InquiryNode *temp = front;
    front = front->next;
    delete temp;
  }
}

// Enqueue a new inquiry
void InquiryQueue::enqueue(const std::string &name, const std::string &email, const std::string &message)
{
  InquiryNode *newInquiry = new InquiryNode(name, email, message);

  if (rear == nullptr)
  {
    front = rear = newInquiry; // First inquiry in an empty queue
  }
  else
  {
    rear->next = newInquiry; // Append the new inquiry to the rear
    rear = newInquiry;
  }
}

// Dequeue the oldest inquiry (FIFO)
InquiryNode *InquiryQueue::dequeue()
{
  if (isEmpty())
  {
    return nullptr;
  }

  InquiryNode *oldFront = front;
  front = front->next;
  if (front == nullptr)
  {
    rear = nullptr; // The queue is now empty
  }

  return oldFront; // Return the removed node
}

// Display all pending inquiries
void InquiryQueue::displayAllInquiries() const
{
  InquiryNode *current = front;
  if (isEmpty())
  {
    std::cout << "No inquiries available.\n";
    return;
  }
  while (current != nullptr)
  {
    std::cout << "Customer Name: " << current->customerName << "\n";
    std::cout << "Customer Email: " << current->customerEmail << "\n";
    std::cout << "Inquiry Message: " << current->inquiryMessage << "\n";
    std::cout << "-------------------------------\n";
    current = current->next;
  }
}

// Check if the queue is empty
bool InquiryQueue::isEmpty() const
{
  return front == nullptr;
}