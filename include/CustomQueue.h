#ifndef CUSTOM_QUEUE_H
#define CUSTOM_QUEUE_H

#include <iostream>
#include <stdexcept>
#include "Inquiry.h"

class CustomQueue
{
private:
  struct Node
  {
    Inquiry data;
    Node *next;
    Node(const Inquiry &value) : data(value), next(nullptr) {}
  };

  Node *front;
  Node *rear;
  int size;

public:
  CustomQueue();
  ~CustomQueue();

  void enqueue(const Inquiry &value);
  Inquiry dequeue();
  Inquiry peek() const;
  bool isEmpty() const;
  int getSize() const;

  // Copy constructor
  CustomQueue(const CustomQueue &other);

  // Assignment operator
  CustomQueue &operator=(const CustomQueue &other);
};

#endif