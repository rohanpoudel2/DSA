#include "PromoManager.h"
#include "CircularLinkedList.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

PromoManager::PromoManager(const std::string &filename) : Database(filename)
{
  createTable();
}

void PromoManager::createTable()
{
  const char *createTableSQL = R"(
        CREATE TABLE IF NOT EXISTS promos (
            promo_id INTEGER PRIMARY KEY AUTOINCREMENT,
            user_id INTEGER NOT NULL,
            discount_percentage INTEGER NOT NULL,
            timestamp TEXT NOT NULL,
            FOREIGN KEY(user_id) REFERENCES users(id)
        );
    )";

  char *errMsg = nullptr;
  if (sqlite3_exec(db, createTableSQL, nullptr, nullptr, &errMsg) != SQLITE_OK)
  {
    std::cerr << "Error creating promos table: " << errMsg << std::endl;
    sqlite3_free(errMsg);
  }
}

PromoManager::~PromoManager()
{
  // The db pointer is handled by the Database class, so no need to close here.
}

void PromoManager::addPromo(const Promo &promo)
{
  const char *sql = "INSERT INTO promos (user_id, discount_percentage, timestamp) VALUES (?, ?, ?);";
  sqlite3_stmt *stmt;

  if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK)
  {
    sqlite3_bind_int(stmt, 1, promo.getUserId());
    sqlite3_bind_int(stmt, 2, promo.getDiscountPercentage());
    sqlite3_bind_text(stmt, 3, promo.getTimestamp().c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
      std::cerr << "Error adding promo: " << sqlite3_errmsg(db) << std::endl;
    }
  }

  sqlite3_finalize(stmt);
}

int PromoManager::spinWheel()
{
  CircularLinkedList discountList;

  discountList.addDiscount(5);
  discountList.addDiscount(10);
  discountList.addDiscount(15);
  discountList.addDiscount(20);
  discountList.addDiscount(25);
  discountList.addDiscount(30);
  discountList.addDiscount(50);

  return discountList.spinWheel();
}

bool PromoManager::userHasPromo(int userId)
{
  const char *sql = "SELECT COUNT(*) FROM promos WHERE user_id = ?;";
  sqlite3_stmt *stmt;
  bool hasPromo = false;

  if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK)
  {
    sqlite3_bind_int(stmt, 1, userId);

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
      int count = sqlite3_column_int(stmt, 0);
      hasPromo = (count > 0);
    }
    else
    {
      std::cerr << "Error checking promo: " << sqlite3_errmsg(db) << std::endl;
    }
  }
  else
  {
    std::cerr << "Error preparing statement: " << sqlite3_errmsg(db) << std::endl;
  }

  sqlite3_finalize(stmt);
  return hasPromo;
}

Promo PromoManager::getUserPromo(int userId)
{
  const char *sql = "SELECT promo_id, discount_percentage, timestamp FROM promos WHERE user_id = ? LIMIT 1;";
  sqlite3_stmt *stmt;

  Promo promo(0, userId, 0, "");

  if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK)
  {
    sqlite3_bind_int(stmt, 1, userId);

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
      int promoId = sqlite3_column_int(stmt, 0);
      int discountPercentage = sqlite3_column_int(stmt, 1);
      std::string timestamp(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2)));

      promo.setPromoId(promoId);
      promo.setUserId(userId);
      promo.setDiscountPercentage(discountPercentage);
      promo.setTimestamp(timestamp);
    }
    else
    {
      std::cerr << "Error retrieving promo: " << sqlite3_errmsg(db) << std::endl;
    }
  }
  else
  {
    std::cerr << "Error preparing statement: " << sqlite3_errmsg(db) << std::endl;
  }

  sqlite3_finalize(stmt);
  return promo;
}