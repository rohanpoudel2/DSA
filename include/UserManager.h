#ifndef USER_MANAGER_H
#define USER_MANAGER_H

#include "Database.h"
#include "User.h"

class UserManager : public Database
{
public:
  UserManager(const std::string &filename);
  void createTable();

  void addUser(const User &user, sqlite3 *db);
  User getCustomerByEmail(const std::string &email, sqlite3 *db);
  bool verifyPassword(int userId, const std::string &hashedPassword, sqlite3 *db);
};

#endif