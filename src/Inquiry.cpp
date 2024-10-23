#include "Inquiry.h"

// Written by Rohan Poudel
Inquiry::Inquiry(const User &user, const std::string &message, const std::string &response, const std::string &timestamp)
    : user(user), message(message), response(response), timestamp(timestamp) {}

// Written by Rohan Poudel
int Inquiry::getInquiryId() const { return inquiryId; }

// Written by Rohan Poudel
const User &Inquiry::getUser() const { return user; }

// Written by Rohan Poudel
std::string Inquiry::getMessage() const { return message; }

// Written by Rohan Poudel
std::string Inquiry::getResponse() const { return response; }

// Written by Rohan Poudel
std::string Inquiry::getTimestamp() const { return timestamp; }

// Written by Rohan Poudel
void Inquiry::setInquiryId(int id) { inquiryId = id; }

// Written by Rohan Poudel
void Inquiry::setUser(const User &userObj) { user = userObj; }

// Written by Rohan Poudel
void Inquiry::setMessage(const std::string &msg) { message = msg; }

// Written by Rohan Poudel
void Inquiry::setResponse(const std::string &resp) { response = resp; }

// Written by Rohan Poudel
void Inquiry::setTimestamp(const std::string &ts) { timestamp = ts; }