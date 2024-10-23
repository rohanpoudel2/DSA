#ifndef INQUIRY_H
#define INQUIRY_H

#include <string>
#include "User.h"

class Inquiry
{
private:
  int inquiryId;
  User user;
  std::string message;
  std::string response;
  std::string timestamp;

public:
  // Constructor for Inquiry
  // Precondition: User object, message, response (optional), and timestamp must be valid non-empty strings
  // Postcondition: An Inquiry object is initialized with provided values
  Inquiry(const User &user, const std::string &message, const std::string &response, const std::string &timestamp);

  // Get the inquiry ID
  // Precondition: Inquiry ID must be set
  // Postcondition: Returns the ID of the inquiry
  int getInquiryId() const;

  // Get the User who made the inquiry
  // Precondition: User must be valid
  // Postcondition: Returns the User associated with the inquiry
  const User &getUser() const;

  // Get the message of the inquiry
  // Precondition: Inquiry must contain a valid message
  // Postcondition: Returns the message of the inquiry
  std::string getMessage() const;

  // Get the response to the inquiry
  // Precondition: Response may be empty if not yet set
  // Postcondition: Returns the response of the inquiry
  std::string getResponse() const;

  // Get the timestamp when the inquiry was created
  // Precondition: Timestamp must be valid and formatted correctly
  // Postcondition: Returns the timestamp of the inquiry
  std::string getTimestamp() const;

  // Set the inquiry ID
  // Precondition: ID must be a valid integer
  // Postcondition: Sets the inquiry ID to the given value
  void setInquiryId(int id);

  // Set the User associated with the inquiry
  // Precondition: A valid User object must be provided
  // Postcondition: Sets the user of the inquiry to the given User
  void setUser(const User &user);

  // Set the message for the inquiry
  // Precondition: Message must be a non-empty string
  // Postcondition: Sets the inquiry message to the provided value
  void setMessage(const std::string &msg);

  // Set the response for the inquiry
  // Precondition: Response can be empty (if not yet responded)
  // Postcondition: Sets the response of the inquiry
  void setResponse(const std::string &resp);

  // Set the timestamp for the inquiry
  // Precondition: Timestamp must be a valid string
  // Postcondition: Sets the timestamp for when the inquiry was created
  void setTimestamp(const std::string &ts);
};

#endif