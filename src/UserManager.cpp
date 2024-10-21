#include "UserManager.h"
#include <iostream>

UserManager::UserManager(const std::string &filename) : Database(filename)
{
  createTables(); // Explicitly create the tables after constructing the base
}

void UserManager::createTables()
{
  const char *createUserTableSQL = R"(
      CREATE TABLE IF NOT EXISTS users (
          id INTEGER PRIMARY KEY AUTOINCREMENT,
          name TEXT NOT NULL,
          email TEXT NOT NULL UNIQUE,
          role TEXT NOT NULL,
          password TEXT NOT NULL
      );
  )";

  char *errMsg = nullptr;
  if (sqlite3_exec(db, createUserTableSQL, nullptr, nullptr, &errMsg) != SQLITE_OK)
  {
    std::cerr << "Error creating users table: " << errMsg << std::endl;
    sqlite3_free(errMsg);
  }
}

// Verify Admin Password
bool UserManager::verifyAdminPassword(const std::string &hashedPassword, sqlite3 *db)
{
  sqlite3_stmt *stmt;
  const char *sql = "SELECT password FROM users WHERE role='admin';";
  bool verified = false;

  if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK)
  {
    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
      std::string storedHash = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
      verified = (storedHash == hashedPassword);
    }
  }
  sqlite3_finalize(stmt);
  return verified;
}

// Add User
void UserManager::addUser(const User &user, sqlite3 *db)
{
  const char *sql = "INSERT INTO users (name, email, role, password) VALUES (?,?,?,?);";
  sqlite3_stmt *stmt;

  if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK)
  {
    sqlite3_bind_text(stmt, 1, user.getName().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, user.getEmail().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, user.getRole().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, user.getPassword().c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
      std::cerr << "Error inserting user: " << sqlite3_errmsg(db) << std::endl;
    }
  }
  sqlite3_finalize(stmt);
}

// Get Customer by Email
User UserManager::getCustomerByEmail(const std::string &email, sqlite3 *db)
{
  const char *sql = "SELECT id, name, email, role, password FROM users WHERE email=?;";
  sqlite3_stmt *stmt;
  User user;

  if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK)
  {
    sqlite3_bind_text(stmt, 1, email.c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
      int id = sqlite3_column_int(stmt, 0);
      std::string name = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
      std::string userEmail = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
      std::string role = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3));
      std::string password = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 4));

      user = User(name, userEmail, role, password);
      user.setId(id);
    }
  }
  sqlite3_finalize(stmt);
  return user;
}