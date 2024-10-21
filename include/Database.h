#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <sqlite3.h>

class Database
{
protected:
  std::string sourceFile; // The source path where the database file will be saved
  sqlite3 *db;            // SQLite3 database connection handle

public:
  // Constructor and Destructor
  Database(const std::string &filename);
  virtual ~Database();

  // Connect to SQLite Database
  sqlite3 *connectToDB(const std::string &dbPath);

  // Create necessary tables
  virtual void createTables() = 0; // Pure virtual function to be implemented by derived classes

  // Getter for db
  sqlite3 *getDB() const { return db; }
};

#endif