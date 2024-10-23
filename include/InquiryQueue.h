#ifndef INQUIRYQUEUE_H
#define INQUIRYQUEUE_H

#include <queue>
#include "Inquiry.h"

class InquiryQueue
{
private:
  std::queue<Inquiry> queue;

public:
  // Constructor
  // Precondition: None
  // Postcondition: Initializes an empty InquiryQueue object.
  InquiryQueue();

  // Enqueue an inquiry into the queue
  // Precondition: inquiry is a valid Inquiry object.
  // Postcondition: Adds the inquiry to the back of the queue.
  void enqueue(const Inquiry &inquiry);

  // Dequeue an inquiry from the front of the queue
  // Precondition: The queue must not be empty.
  // Postcondition: Removes and returns the inquiry at the front of the queue.
  // Throws a runtime error if the queue is empty.
  Inquiry dequeue();

  // Display all inquiries in the queue
  // Precondition: None
  // Postcondition: Prints the details of all inquiries in the queue to the console.
  void displayAllInquiries() const;

  // Check if the queue is empty
  // Precondition: None
  // Postcondition: Returns true if the queue is empty, otherwise false.
  bool isEmpty() const;

  // Peek at the front inquiry of the queue without removing it
  // Precondition: The queue must not be empty.
  // Postcondition: Returns the inquiry at the front of the queue without removing it.
  // Throws a runtime error if the queue is empty.
  Inquiry peekFront() const;
};

#endif