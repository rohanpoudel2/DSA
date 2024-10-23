#include "CircularLinkedList.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

// Written by Rohan Poudel
CircularLinkedList::CircularLinkedList() : head(nullptr) {}

// Written by Rohan Poudel
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

// Written by Rohan Poudel
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

// Written by Rohan Poudel
bool CircularLinkedList::isEmpty() const
{
  return head == nullptr;
}

// Written by Rohan Poudel
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