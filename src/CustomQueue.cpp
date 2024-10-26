#include "CustomQueue.h"

CustomQueue::CustomQueue() : front(nullptr), rear(nullptr), size(0) {}

CustomQueue::~CustomQueue()
{
  while (!isEmpty())
  {
    dequeue();
  }
}

void CustomQueue::enqueue(const Inquiry &value)
{
  Node *newNode = new Node(value);
  if (rear == nullptr)
  {
    front = rear = newNode;
  }
  else
  {
    rear->next = newNode;
    rear = newNode;
  }
  size++;
}

Inquiry CustomQueue::dequeue()
{
  if (isEmpty())
  {
    throw std::runtime_error("Queue is empty. Cannot dequeue.");
  }

  Node *temp = front;
  Inquiry data = temp->data;
  front = front->next;
  if (front == nullptr)
  {
    rear = nullptr;
  }
  delete temp;
  size--;
  return data;
}

Inquiry CustomQueue::peek() const
{
  if (isEmpty())
  {
    throw std::runtime_error("Queue is empty. Cannot peek.");
  }
  return front->data;
}

bool CustomQueue::isEmpty() const
{
  return front == nullptr;
}

int CustomQueue::getSize() const
{
  return size;
}

// Copy constructor
CustomQueue::CustomQueue(const CustomQueue &other) : front(nullptr), rear(nullptr), size(0)
{
  Node *current = other.front;
  while (current != nullptr)
  {
    enqueue(current->data);
    current = current->next;
  }
}

// Assignment operator
CustomQueue &CustomQueue::operator=(const CustomQueue &other)
{
  if (this != &other)
  {
    while (!isEmpty())
    {
      dequeue();
    }

    Node *current = other.front;
    while (current != nullptr)
    {
      enqueue(current->data);
      current = current->next;
    }
  }
  return *this;
}