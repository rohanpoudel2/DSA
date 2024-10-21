#ifndef INQUIRY_H
#define INQUIRY_H

#include <string>
#include "User.h" // Include the User class

class Inquiry
{
private:
  int inquiryId;         // Unique ID for the inquiry
  User user;             // User who made the inquiry
  std::string message;   // The actual inquiry message
  std::string response;  // The response to the inquiry
  std::string timestamp; // Timestamp of when the inquiry was created

public:
  // Constructor
  Inquiry(const User &user, const std::string &message, const std::string &timestamp);

  // Getters
  int getInquiryId() const;
  const User &getUser() const; // Return the User object
  std::string getMessage() const;
  std::string getResponse() const;
  std::string getTimestamp() const;

  // Setters
  void setInquiryId(int id);
  void setUser(const User &user);
  void setMessage(const std::string &msg);
  void setResponse(const std::string &resp);
  void setTimestamp(const std::string &ts);
};

#endif