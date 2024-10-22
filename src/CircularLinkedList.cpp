#include "CircularLinkedList.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

CircularLinkedList::CircularLinkedList() : head(nullptr) {}

CircularLinkedList::~CircularLinkedList()
{
  if (head)
  {
    CircularNode *current = head;
    CircularNode *nextNode;
    do
    {
      nextNode = current->next;
      delete current;
      current = nextNode;
    } while (current != head);
  }
}

void CircularLinkedList::addDiscount(int discount)
{
  CircularNode *newNode = new CircularNode(discount);
  if (isEmpty())
  {
    head = newNode;
    head->next = head;
  }
  else
  {
    CircularNode *temp = head;
    while (temp->next != head)
    {
      temp = temp->next;
    }
    temp->next = newNode;
    newNode->next = head;
  }
}

bool CircularLinkedList::isEmpty() const
{
  return head == nullptr;
}

int CircularLinkedList::spinWheel()
{
  if (isEmpty())
  {
    std::cerr << "No discounts available!" << std::endl;
    return 0;
  }

  srand(static_cast<unsigned int>(time(nullptr)));
  int steps = rand() % 10 + 1;

  CircularNode *current = head;
  for (int i = 0; i < steps; ++i)
  {
    current = current->next;
  }

  return current->discountPercentage;
}