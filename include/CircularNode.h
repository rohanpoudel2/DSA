#ifndef CIRCULAR_NODE_H
#define CIRCULAR_NODE_H

struct CircularNode
{
  int discountPercentage;
  CircularNode *next;

  CircularNode(int discountPercentage) : discountPercentage(discountPercentage), next(nullptr) {}
};

#endif