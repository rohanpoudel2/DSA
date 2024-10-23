#ifndef USER_MANAGER_H
#define USER_MANAGER_H

#include "Database.h"
#include "User.h"

class UserManager : public Database
{
public:
  // Constructor
  // Precondition: 'filename' must be a valid path to the SQLite database file.
  // Postcondition: Initializes the UserManager with the given database file and connects to the database.
  UserManager(const std::string &filename);

  // Method to create the users table in the database.
  // Precondition: The database must be connected.
  // Postcondition: Ensures the 'users' table exists in the database. If it doesn't exist, it creates the table.
  void createTable();

  // Method to add a new user to the database.
  // Precondition: 'user' must contain valid name, email, role, and password. 'db' must be a valid SQLite connection.
  // Postcondition: Inserts the new user into the 'users' table in the database.
  void addUser(const User &user, sqlite3 *db);

  // Method to retrieve a customer by their email from the database.
  // Precondition: 'email' must be a valid email format. 'db' must be a valid SQLite connection.
  // Postcondition: Returns a User object corresponding to the customer with the given email. If no such customer exists, returns a default User object.
  User getCustomerByEmail(const std::string &email, sqlite3 *db);

  // Method to verify the password for a given user.
  // Precondition: 'userId' must be a valid user ID. 'hashedPassword' must be the hashed version of the password. 'db' must be a valid SQLite connection.
  // Postcondition: Returns 'true' if the password matches the user's stored password, otherwise returns 'false'.
  bool verifyPassword(int userId, const std::string &hashedPassword, sqlite3 *db);
};

#endif