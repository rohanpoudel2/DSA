#include <gtest/gtest.h>
#include "Database.h"
#include <sqlite3.h>

// Helper function to check if a table exists in the database
bool tableExists(sqlite3 *db, const std::string &tableName)
{
  std::string sql = "SELECT name FROM sqlite_master WHERE type='table' AND name='" + tableName + "';";
  sqlite3_stmt *stmt;
  bool exists = false;

  if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK)
  {
    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
      exists = true;
    }
  }
  sqlite3_finalize(stmt);
  return exists;
}

// Test creating tables using the Database class
TEST(DatabaseTest, CreateTables)
{
  const std::string filePath = "./data/store_test.db";

  // Initialize Database class
  Database db(filePath);

  // Check if the connection is established
  ASSERT_NE(db.getDB(), nullptr) << "Failed to connect to the database.";

  // Create tables in the database
  db.createTables();

  // Verify if essential tables were created
  sqlite3 *connection = db.getDB();
  EXPECT_TRUE(tableExists(connection, "users")) << "Users table was not created.";
  EXPECT_TRUE(tableExists(connection, "products")) << "Products table was not created.";
  EXPECT_TRUE(tableExists(connection, "inquiries")) << "Inquiries table was not created.";
  EXPECT_TRUE(tableExists(connection, "promos")) << "Promos table was not created.";
}