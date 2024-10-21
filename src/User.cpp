#include "User.h"

// Default constructor
User::User() : id(0), name(""), email(""), role("customer"), password("") {}

// Parameterized constructor
User::User(const std::string &name, const std::string &email, const std::string &role, const std::string &password)
    : name(name), email(email), role(role), password(password) {}

int User::getId() const { return id; }
std::string User::getName() const { return name; }
std::string User::getEmail() const { return email; }
std::string User::getRole() const { return role; }
std::string User::getPassword() const { return password; }

void User::setId(int id) { this->id = id; }
void User::setName(const std::string &name) { this->name = name; }
void User::setEmail(const std::string &email) { this->email = email; }
void User::setRole(const std::string &role) { this->role = role; }
void User::setPassword(const std::string &password) { this->password = password; }

bool User::isAdmin() const { return role == "admin"; }