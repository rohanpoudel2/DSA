#ifndef CIRCULAR_LINKED_LIST_H
#define CIRCULAR_LINKED_LIST_H

#include "CircularNode.h"

class CircularLinkedList
{
private:
  CircularNode *head; // Pointer to the head node of the circular linked list

public:
  // Constructor
  // Precondition: None.
  // Postcondition: Initializes an empty circular linked list with the head set to nullptr.
  CircularLinkedList();

  // Destructor
  // Precondition: None.
  // Postcondition: Frees all nodes in the circular linked list.
  ~CircularLinkedList();

  // Adds a discount to the circular linked list
  // Precondition: discount is a valid integer representing a discount percentage.
  // Postcondition: A new node with the given discount percentage is added to the circular linked list.
  void addDiscount(int discount);

  // Spins the wheel and returns a random discount from the list
  // Precondition: The circular linked list must contain at least one node.
  // Postcondition: Returns an integer representing a randomly selected discount percentage from the list.
  int spinWheel();

  // Checks if the circular linked list is empty
  // Precondition: None.
  // Postcondition: Returns true if the circular linked list contains no nodes, otherwise false.
  bool isEmpty() const;
};

#endif