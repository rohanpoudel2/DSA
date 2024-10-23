#include "Database.h"
#include "UserManager.h"
#include "ProductManager.h"
#include "InquiryManager.h"
#include "PromoManager.h"
#include <sqlite3.h>
#include <iostream>

// Written by Rohan Poudel
Database::Database(const std::string &filename) : sourceFile(filename)
{
  db = connectToDB(sourceFile);
}

// Written by Rohan Poudel
Database::~Database()
{
  if (db)
  {
    sqlite3_close(db);
  }
}

// Written by Rohan Poudel
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

// Written by Rohan Poudel
void Database::createTables()
{
  UserManager userDB(sourceFile);
  userDB.createTable();

  ProductManager productDB(sourceFile);
  productDB.createTable();

  InquiryManager inquiryDB(sourceFile);
  inquiryDB.createTable();

  PromoManager promoDB(sourceFile);
  promoDB.createTable();
}