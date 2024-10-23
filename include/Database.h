#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <sqlite3.h>

class Database
{
protected:
  std::string sourceFile; // Stores the path to the database file
  sqlite3 *db;            // SQLite database connection

public:
  // Constructor: Initializes a Database object and connects to the SQLite database.
  // Precondition: `filename` must be a valid file path where the database can be opened or created.
  // Postcondition: The `db` member will be initialized with an open connection to the SQLite database.
  Database(const std::string &filename);

  // Destructor: Closes the SQLite database connection if open.
  // Precondition: None.
  // Postcondition: The SQLite database connection is closed.
  virtual ~Database();

  // Method to connect to the SQLite database.
  // Precondition: `dbPath` must be a valid file path where the SQLite database is stored or will be created.
  // Postcondition: Returns a pointer to the SQLite database connection.
  // If the connection fails, it returns a null pointer.
  sqlite3 *connectToDB(const std::string &dbPath);

  // Method to create the necessary tables in the database.
  // Precondition: Derived classes must implement specific table creation logic.
  // Postcondition: The required tables for the derived class are created in the SQLite database.
  void createTables();

  // Getter for the SQLite database connection.
  // Precondition: The database connection (`db`) should be initialized.
  // Postcondition: Returns a pointer to the active SQLite database connection.
  sqlite3 *getDB() const { return db; }
};

#endif