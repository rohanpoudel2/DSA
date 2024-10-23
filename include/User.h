#ifndef USER_H
#define USER_H

#include <string>
#include <sqlite3.h>

class User
{
private:
  int id;               // Unique user ID
  std::string name;     // User's name
  std::string email;    // User's email address
  std::string role;     // Role of the user (e.g., "admin" or "customer")
  std::string password; // Hashed password of the user

public:
  // Default constructor
  // Precondition: None
  // Postcondition: Initializes an empty User object
  User();

  // Parameterized constructor
  // Precondition: All parameters (name, email, role, password) should be valid strings
  // Postcondition: Initializes a User object with given name, email, role, and password
  User(const std::string &name, const std::string &email, const std::string &role, const std::string &password);

  // Getter for user ID
  // Precondition: None
  // Postcondition: Returns the user's ID
  int getId() const;

  // Getter for user name
  // Precondition: None
  // Postcondition: Returns the user's name
  std::string getName() const;

  // Getter for user email
  // Precondition: None
  // Postcondition: Returns the user's email address
  std::string getEmail() const;

  // Getter for user role
  // Precondition: None
  // Postcondition: Returns the user's role (admin or customer)
  std::string getRole() const;

  // Getter for user password
  // Precondition: None
  // Postcondition: Returns the user's hashed password
  std::string getPassword() const;

  // Setter for user ID
  // Precondition: The ID must be a valid integer
  // Postcondition: Sets the user's ID to the provided value
  void setId(int id);

  // Setter for user name
  // Precondition: The name must be a valid string
  // Postcondition: Sets the user's name to the provided value
  void setName(const std::string &name);

  // Setter for user email
  // Precondition: The email must be a valid string
  // Postcondition: Sets the user's email to the provided value
  void setEmail(const std::string &email);

  // Setter for user role
  // Precondition: The role must be a valid string (admin or customer)
  // Postcondition: Sets the user's role to the provided value
  void setRole(const std::string &role);

  // Setter for user password
  // Precondition: The password must be a valid string (hashed)
  // Postcondition: Sets the user's password to the provided value
  void setPassword(const std::string &password);

  // Check if user is an admin
  // Precondition: None
  // Postcondition: Returns true if the user's role is "admin", otherwise false
  bool isAdmin() const;

  // Static method to fetch user by ID from the database
  // Precondition: The userId must be valid and the database connection must be active
  // Postcondition: Returns a User object fetched from the database
  static User getUserById(int userId, sqlite3 *db);
};

#endif