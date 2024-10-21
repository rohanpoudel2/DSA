#include "Database.h"
#include "UserManager.h"
#include "ProductManager.h"
#include "InquiryManager.h"
#include <sqlite3.h>
#include <iostream>

// Constructor initializes the database with the given file path
Database::Database(const std::string &filename) : sourceFile(filename)
{
  db = connectToDB(sourceFile);
}

// Destructor to close the database connection
Database::~Database()
{
  if (db)
  {
    sqlite3_close(db);
  }
}

// Connect to SQLite Database
sqlite3 *Database::connectToDB(const std::string &dbPath)
{
  sqlite3 *db;
  if (sqlite3_open(dbPath.c_str(), &db))
  {
    std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
    return nullptr;
  }
  return db;
}

// Create necessary tables for all modules
void Database::createTables()
{
  // Create user table
  UserManager userDB(sourceFile);
  userDB.createTables();

  // Create product table
  ProductManager productDB(sourceFile);
  productDB.createTables();

  // Create inquiry table
  InquiryManager inquiryDB(sourceFile);
  inquiryDB.createTables();
}