#include "InquiryManager.h"
#include <iostream>
#include <sqlite3.h>

InquiryManager::InquiryManager(const std::string &filename) : Database(filename)
{
  createTables();
}

void InquiryManager::createTables()
{
  const char *createInquiryTableSQL = R"(
    CREATE TABLE IF NOT EXISTS inquiries (
        inquiry_id INTEGER PRIMARY KEY AUTOINCREMENT,
        user_id INTEGER NOT NULL,
        message TEXT NOT NULL,
        response TEXT,
        timestamp TEXT DEFAULT CURRENT_TIMESTAMP,
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

void InquiryManager::saveInquiryResponseToDB(const Inquiry &inquiry)
{
  const char *sql = "UPDATE inquiries SET response = ? WHERE inquiry_id = ?;";
  sqlite3_stmt *stmt;

  if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK)
  {
    sqlite3_bind_text(stmt, 1, inquiry.getResponse().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, inquiry.getInquiryId());

    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
      std::cerr << "Error updating inquiry response: " << sqlite3_errmsg(db) << std::endl;
    }
  }
  sqlite3_finalize(stmt);
}

void InquiryManager::saveInquiryToDB(const Inquiry &inquiry)
{
  const char *sql = "INSERT INTO inquiries (user_id, message, timestamp) VALUES (?, ?, ?);";
  sqlite3_stmt *stmt;

  if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK)
  {
    sqlite3_bind_int(stmt, 1, inquiry.getUser().getId());
    sqlite3_bind_text(stmt, 2, inquiry.getMessage().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, inquiry.getTimestamp().c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
      std::cerr << "Error inserting inquiry: " << sqlite3_errmsg(db) << std::endl;
    }
    sqlite3_finalize(stmt);
  }
  else
  {
    std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
  }
}

InquiryQueue InquiryManager::loadInquiriesForUser(int userId)
{
  InquiryQueue inquiryQueue;
  const char *sql = "SELECT inquiry_id, user_id, message, response ,timestamp FROM inquiries WHERE user_id = ?;";
  sqlite3_stmt *stmt;

  if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK)
  {
    sqlite3_bind_int(stmt, 1, userId);

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
      User user = User::getUserById(userId, db);
      int fetchedUserId = sqlite3_column_int(stmt, 1);
      std::string message = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
      std::string response = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3));
      std::string timestamp = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 4));

      Inquiry inquiry(user, message, response, timestamp);
      inquiryQueue.enqueue(inquiry);
    }
  }
  else
  {
    std::cerr << "Failed to fetch inquiries: " << sqlite3_errmsg(db) << std::endl;
  }

  sqlite3_finalize(stmt);
  return inquiryQueue;
}

void InquiryManager::removeInquiryFromDB(int inquiryId)
{
  const char *sql = "DELETE FROM inquiries WHERE inquiry_id = ?;";
  sqlite3_stmt *stmt;

  if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK)
  {
    sqlite3_bind_int(stmt, 1, inquiryId);
    sqlite3_step(stmt);
  }

  sqlite3_finalize(stmt);
}

InquiryQueue InquiryManager::loadAllInquiriesWithNoResponses()
{
  InquiryQueue inquiryQueue;
  const char *sql = "SELECT inquiry_id, user_id, message, timestamp FROM inquiries WHERE response IS NULL;";
  sqlite3_stmt *stmt;

  if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK)
  {
    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
      int inquiryId = sqlite3_column_int(stmt, 0);
      int userId = sqlite3_column_int(stmt, 1);
      std::string message = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
      std::string timestamp = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3));

      User user = User::getUserById(userId, db);
      Inquiry inquiry(user, message, "", timestamp);
      inquiry.setInquiryId(inquiryId);
      inquiryQueue.enqueue(inquiry);
    }
  }
  else
  {
    std::cerr << "Failed to fetch inquiries with no responses: " << sqlite3_errmsg(db) << std::endl;
  }

  sqlite3_finalize(stmt);
  return inquiryQueue;
}
