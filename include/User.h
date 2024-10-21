#ifndef USER_H
#define USER_H

#include <string>
#include <sqlite3.h>

class User
{
private:
  int id;
  std::string name;
  std::string email;
  std::string role;
  std::string password; // Fixed typo here

public:
  // Default constructor
  User();

  // Parameterized constructor
  User(const std::string &name, const std::string &email, const std::string &role, const std::string &password);

  int getId() const;
  std::string getName() const;
  std::string getEmail() const;
  std::string getRole() const;
  std::string getPassword() const;

  void setId(int id);
  void setName(const std::string &name);
  void setEmail(const std::string &email);
  void setRole(const std::string &role);
  void setPassword(const std::string &password);

  // Check if user is admin
  bool isAdmin() const;

  static User getUserById(int userId, sqlite3 *db);
};

#endif // USER_H