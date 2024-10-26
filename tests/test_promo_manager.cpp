#include <gtest/gtest.h>
#include "PromoManager.h"
#include "UserManager.h"
#include "Promo.h"
#include "Utils.h"
#include "Environment.h"
#include <sqlite3.h>

// Helper function to clean the promos database
bool cleanPromoDatabase(const std::string &filePath)
{
  sqlite3 *db;
  if (sqlite3_open(filePath.c_str(), &db) != SQLITE_OK)
  {
    std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
    return false;
  }

  const char *sqlClear = "DELETE FROM promos;";
  char *errMsg = nullptr;
  if (sqlite3_exec(db, sqlClear, nullptr, nullptr, &errMsg) != SQLITE_OK)
  {
    std::cerr << "SQL error: " << errMsg << std::endl;
    sqlite3_free(errMsg);
    return false;
  }

  sqlite3_close(db);
  return true;
}

// Helper function to clean the users database
bool cleanUserDatabase(const std::string &filePath)
{
  sqlite3 *db;
  if (sqlite3_open(filePath.c_str(), &db) != SQLITE_OK)
  {
    std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
    return false;
  }

  const char *sqlClear = "DELETE FROM users;";
  char *errMsg = nullptr;
  if (sqlite3_exec(db, sqlClear, nullptr, nullptr, &errMsg) != SQLITE_OK)
  {
    std::cerr << "SQL error: " << errMsg << std::endl;
    sqlite3_free(errMsg);
    return false;
  }

  sqlite3_close(db);
  return true;
}

TEST(PromoManagerTest, CreateTable)
{
  std::string testDBPath = Utils::getDatabasePath(Environment::environment);
  PromoManager promoManager(testDBPath);

  // Assuming table creation will not throw an error, we pass the test
  SUCCEED();
}

// Test adding a promo to the database and retrieving it
TEST(PromoManagerTest, AddPromoAndRetrieve)
{
  std::string testDBPath = Utils::getDatabasePath(Environment::environment);
  ASSERT_TRUE(cleanPromoDatabase(testDBPath)); // Ensure promos table is clean

  PromoManager promoManager(testDBPath);
  UserManager userManager(testDBPath);

  User user("Alice", "alice@example.com", "customer", "password123");
  userManager.addUser(user, userManager.getDB());
  user = userManager.getCustomerByEmail("alice@example.com", userManager.getDB());

  Promo promo(0, user.getId(), 20, "2023-10-20 12:34:56");
  promoManager.addPromo(promo);

  // Check if the user has a promo
  EXPECT_TRUE(promoManager.userHasPromo(user.getId()));

  // Retrieve the user's promo
  Promo retrievedPromo = promoManager.getUserPromo(user.getId());
  EXPECT_EQ(retrievedPromo.getDiscountPercentage(), 20);
  EXPECT_EQ(retrievedPromo.getTimestamp(), "2023-10-20 12:34:56");
}

// Test the spinWheel function
TEST(PromoManagerTest, SpinWheel)
{
  std::string testDBPath = Utils::getDatabasePath(Environment::environment);
  PromoManager promoManager(testDBPath);

  // Spin the wheel multiple times to check the validity of discounts
  for (int i = 0; i < 10; ++i)
  {
    int discount = promoManager.spinWheel();
    EXPECT_TRUE(discount == 5 || discount == 10 || discount == 15 || discount == 20 || discount == 25 || discount == 30 || discount == 50);
  }
}

// Test checking if a user has no promo
TEST(PromoManagerTest, UserHasNoPromo)
{
  std::string testDBPath = Utils::getDatabasePath(Environment::environment);
  ASSERT_TRUE(cleanPromoDatabase(testDBPath)); // Ensure promos table is clean
  ASSERT_TRUE(cleanUserDatabase(testDBPath));  // Ensure users table is clean

  PromoManager promoManager(testDBPath);
  UserManager userManager(testDBPath);

  User user("Bob", "bob@example.com", "customer", "password456");
  userManager.addUser(user, userManager.getDB());
  user = userManager.getCustomerByEmail("bob@example.com", userManager.getDB());

  // Check if the user has no promo
  EXPECT_FALSE(promoManager.userHasPromo(user.getId()));
}