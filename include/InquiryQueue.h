#ifndef INQUIRYQUEUE_H
#define INQUIRYQUEUE_H

#include <queue>
#include "Inquiry.h"

class InquiryQueue
{
private:
  std::queue<Inquiry> queue; // Queue of Inquiry objects

public:
  // Constructor initializes an empty queue
  InquiryQueue();

  // Add a new inquiry to the rear of the queue
  void enqueue(const Inquiry &inquiry);

  // Remove and return the inquiry at the front of the queue
  Inquiry dequeue();

  // View all inquiries
  void displayAllInquiries() const;

  // Check if the queue is empty
  bool isEmpty() const;

  // Peek the front inquiry without dequeuing
  Inquiry peekFront() const;
};

#endif