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
  Inquiry(const User &user, const std::string &message, const std::string &response, const std::string &timestamp);

  int getInquiryId() const;
  const User &getUser() const;
  std::string getMessage() const;
  std::string getResponse() const;
  std::string getTimestamp() const;

  void setInquiryId(int id);
  void setUser(const User &user);
  void setMessage(const std::string &msg);
  void setResponse(const std::string &resp);
  void setTimestamp(const std::string &ts);
};

#endif