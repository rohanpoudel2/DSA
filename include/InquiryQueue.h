#ifndef INQUIRYQUEUE_H
#define INQUIRYQUEUE_H

#include <queue>
#include "Inquiry.h"

class InquiryQueue
{
private:
  std::queue<Inquiry> queue;

public:
  InquiryQueue();

  void enqueue(const Inquiry &inquiry);

  Inquiry dequeue();

  void displayAllInquiries() const;

  bool isEmpty() const;

  Inquiry peekFront() const;
};

#endif