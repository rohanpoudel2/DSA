#ifndef CIRCULAR_LINKED_LIST_H
#define CIRCULAR_LINKED_LIST_H

#include "CircularNode.h"

class CircularLinkedList
{
private:
  CircularNode *head;

public:
  CircularLinkedList();

  ~CircularLinkedList();

  void addDiscount(int discount);

  int spinWheel();

  bool isEmpty() const;
};

#endif