#include "InquiryManager.h"
#include <iostream>

InquiryManager::InquiryManager(const std::string &filename) : Database(filename)
{
  db = connectToDB(sourceFile);
  if (db != nullptr)
  {
    createTables(); // Ensure necessary tables are created
  }
}

// Create inquiry table
void InquiryManager::createTables()
{
  const char *createInquiryTableSQL = R"(
      CREATE TABLE IF NOT EXISTS inquiries (
          inquiry_id INTEGER PRIMARY KEY AUTOINCREMENT,
          user_id INTEGER NOT NULL,
          inquiry_message TEXT NOT NULL,
          inquiry_timestamp DATETIME DEFAULT CURRENT_TIMESTAMP,
          FOREIGN KEY (user_id) REFERENCES users(id)
      );
  )";

  char *errMsg = nullptr;
  if (sqlite3_exec(db, createInquiryTableSQL, nullptr, nullptr, &errMsg) != SQLITE_OK)
  {
    std::cerr << "Error creating inquiries table: " << errMsg << std::endl;
    sqlite3_free(errMsg);
  }
}

// Save an inquiry to the database
void InquiryManager::saveInquiryToDB(const InquiryNode &inquiry, int user_id)
{
  const char *sql = "INSERT INTO inquiries (user_id, inquiry_message) VALUES (?,?);";
  sqlite3_stmt *stmt;

  if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK)
  {
    sqlite3_bind_int(stmt, 1, user_id);
    sqlite3_bind_text(stmt, 2, inquiry.inquiryMessage.c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
      std::cerr << "Error inserting inquiry: " << sqlite3_errmsg(db) << std::endl;
    }
  }
  sqlite3_finalize(stmt);
}

// Load the next inquiry from the database
InquiryNode *InquiryManager::loadNextInquiryFromDB()
{
  const char *sql = "SELECT inquiry_id, user_id, inquiry_message FROM inquiries ORDER BY inquiry_timestamp ASC LIMIT 1;";
  sqlite3_stmt *stmt;
  InquiryNode *inquiry = nullptr;

  if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK)
  {
    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
      std::string message = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));

      inquiry = new InquiryNode("", "", message); // Leaving name and email blank
      int inquiry_id = sqlite3_column_int(stmt, 0);
      removeInquiryFromDB(inquiry_id); // Remove inquiry after processing
    }
  }

  sqlite3_finalize(stmt);
  return inquiry;
}

// Remove inquiry after processing
void InquiryManager::removeInquiryFromDB(int inquiry_id)
{
  const char *sql = "DELETE FROM inquiries WHERE inquiry_id = ?;";
  sqlite3_stmt *stmt;

  if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK)
  {
    sqlite3_bind_int(stmt, 1, inquiry_id);
    sqlite3_step(stmt);
  }

  sqlite3_finalize(stmt);
}