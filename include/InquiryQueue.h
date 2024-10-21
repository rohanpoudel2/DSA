#ifndef INQUIRYQUEUE_H
#define INQUIRYQUEUE_H

#include <string>

// Inquiry node structure
struct InquiryNode
{
  std::string customerName;
  std::string customerEmail;
  std::string inquiryMessage;

  InquiryNode *next;
  InquiryNode(const std::string &name, const std::string &email, const std::string &message) : customerName(name), customerEmail(email), inquiryMessage(message), next(nullptr) {}
};

class InquiryQueue
{
private:
  InquiryNode *front; // Pointer to the first inquiry
  InquiryNode *rear;  // Pointer to the last inquiry

public:
  // Constructor initializes an empty queue
  InquiryQueue();

  // Destructor frees all allocated memory
  ~InquiryQueue();

  // Add a new inquiry to the rear of the queue
  void enqueue(const std::string &name, const std::string &email, const std::string &message);

  // Remove and return the inquiry at the front of the queue
  InquiryNode *dequeue();

  // View all inquiries
  void displayAllInquiries() const;

  // Check if the queue is empty
  bool isEmpty() const;
};

#endif