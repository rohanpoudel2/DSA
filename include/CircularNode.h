#ifndef CIRCULAR_NODE_H
#define CIRCULAR_NODE_H

// CircularNode represents a node in a circular linked list structure
struct CircularNode
{
  int discountPercentage; // The discount percentage stored in the node
  CircularNode *next;     // Pointer to the next node in the list

  // Constructor
  // Precondition: discountPercentage is an integer value representing a discount.
  // Postcondition: Creates a CircularNode with the given discount percentage and sets the next pointer to nullptr.
  CircularNode(int discountPercentage) : discountPercentage(discountPercentage), next(nullptr) {}
};

#endif