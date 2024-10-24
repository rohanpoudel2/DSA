#ifndef CUSTOM_QUEUE_H
#define CUSTOM_QUEUE_H

#include <iostream>
#include <stdexcept>

template <typename T>
class CustomQueue
{
private:
  struct Node
  {
    T data;
    Node *next;
    Node(const T &value) : data(value), next(nullptr) {}
  };

  Node *front;
  Node *rear;
  int size;

public:
  CustomQueue() : front(nullptr), rear(nullptr), size(0) {}
  ~CustomQueue();

  void enqueue(const T &value);
  T dequeue();
  T peek() const;
  bool isEmpty() const;
  int getSize() const;
};

// Destructor to clean up the queue
template <typename T>
CustomQueue<T>::~CustomQueue()
{
  while (!isEmpty())
  {
    dequeue();
  }
}

// Enqueue a value
template <typename T>
void CustomQueue<T>::enqueue(const T &value)
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

// Dequeue a value
template <typename T>
T CustomQueue<T>::dequeue()
{
  if (isEmpty())
  {
    throw std::runtime_error("Queue is empty. Cannot dequeue.");
  }

  Node *temp = front;
  T data = temp->data;
  front = front->next;
  if (front == nullptr)
  {
    rear = nullptr;
  }
  delete temp;
  size--;
  return data;
}

// Peek at the front element without removing it
template <typename T>
T CustomQueue<T>::peek() const
{
  if (isEmpty())
  {
    throw std::runtime_error("Queue is empty. Cannot peek.");
  }
  return front->data;
}

// Check if the queue is empty
template <typename T>
bool CustomQueue<T>::isEmpty() const
{
  return front == nullptr;
}

// Get the size of the queue
template <typename T>
int CustomQueue<T>::getSize() const
{
  return size;
}

#endif