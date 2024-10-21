#include "Inquiry.h"

// Constructor
Inquiry::Inquiry(const User &user, const std::string &message, const std::string &timestamp)
    : user(user), message(message), timestamp(timestamp) {}

// Getters
int Inquiry::getInquiryId() const { return inquiryId; }
const User &Inquiry::getUser() const { return user; }
std::string Inquiry::getMessage() const { return message; }
std::string Inquiry::getResponse() const { return response; }
std::string Inquiry::getTimestamp() const { return timestamp; }

// Setters
void Inquiry::setInquiryId(int id) { inquiryId = id; }
void Inquiry::setUser(const User &userObj) { user = userObj; }
void Inquiry::setMessage(const std::string &msg) { message = msg; }
void Inquiry::setResponse(const std::string &resp) { response = resp; }
void Inquiry::setTimestamp(const std::string &ts) { timestamp = ts; }