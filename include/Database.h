#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <sqlite3.h>

class Database
{
protected:
  std::string sourceFile;
  sqlite3 *db;

public:
  Database(const std::string &filename);
  virtual ~Database();

  sqlite3 *connectToDB(const std::string &dbPath);

  void createTables();

  sqlite3 *getDB() const { return db; }
};

#endif