#include <gtest/gtest.h>
#include "UserManager.h"
#include "User.h"
#include "Utils.h"
#include <fstream>
#include <cstdio>
#include "Environment.h"

// Helper function to clean up database after tests
void removeTestDB(const std::string &dbPath)
{
  std::remove(dbPath.c_str());
}

// Test fixture for UserManager
class UserManagerTest : public ::testing::Test
{
protected:
  std::string testDBPath = Utils::getDatabasePath(Environment::environment);
  UserManager *userManager;

  void SetUp() override
  {
    userManager = new UserManager(testDBPath);
  }

  void TearDown() override
  {
    delete userManager;
    removeTestDB(testDBPath); // Clean up the database file after test
  }
};

// Test for creating the users table
TEST_F(UserManagerTest, CreateUserTable)
{
  // Table creation is done in the constructor, so we just need to check if it exists
  sqlite3 *db;
  sqlite3_open(testDBPath.c_str(), &db);

  const char *sql = "SELECT name FROM sqlite_master WHERE type='table' AND name='users';";
  sqlite3_stmt *stmt;

  ASSERT_EQ(sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr), SQLITE_OK);
  ASSERT_EQ(sqlite3_step(stmt), SQLITE_ROW); // Check if the table is created

  sqlite3_finalize(stmt);
  sqlite3_close(db);
}

// Test for adding a user
TEST_F(UserManagerTest, AddUser)
{
  User newUser("John Doe", "johndoe@example.com", "customer", "hashedPassword123");
  sqlite3 *db;
  sqlite3_open(testDBPath.c_str(), &db);

  // Add user
  userManager->addUser(newUser, db);

  // Check if the user was inserted
  const char *sql = "SELECT name, email, role FROM users WHERE email='johndoe@example.com';";
  sqlite3_stmt *stmt;

  ASSERT_EQ(sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr), SQLITE_OK);
  ASSERT_EQ(sqlite3_step(stmt), SQLITE_ROW); // User should exist

  std::string name = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
  std::string email = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
  std::string role = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));

  EXPECT_EQ(name, "John Doe");
  EXPECT_EQ(email, "johndoe@example.com");
  EXPECT_EQ(role, "customer");

  sqlite3_finalize(stmt);
  sqlite3_close(db);
}

// Test for getting a user by email
TEST_F(UserManagerTest, GetUserByEmail)
{
  User newUser("Jane Doe", "janedoe@example.com", "customer", "hashedPassword456");
  sqlite3 *db;
  sqlite3_open(testDBPath.c_str(), &db);

  // Add user
  userManager->addUser(newUser, db);

  // Retrieve user by email
  User fetchedUser = userManager->getCustomerByEmail("janedoe@example.com", db);

  EXPECT_EQ(fetchedUser.getName(), "Jane Doe");
  EXPECT_EQ(fetchedUser.getEmail(), "janedoe@example.com");
  EXPECT_EQ(fetchedUser.getRole(), "customer");

  sqlite3_close(db);
}

TEST_F(UserManagerTest, VerifyPassword)
{
  std::string plainPassword = "mypassword";
  std::string hashedPassword = Utils::hashPassword(plainPassword);
  User newUser("Jake Doe", "jakedoe@example.com", "customer", hashedPassword);
  sqlite3 *db;
  sqlite3_open(testDBPath.c_str(), &db);

  // Add user with hashed password
  userManager->addUser(newUser, db);

  // Retrieve the user from the database (to ensure ID is correct)
  User fetchedUser = userManager->getCustomerByEmail("jakedoe@example.com", db);

  // Verify correct password
  bool isPasswordCorrect = userManager->verifyPassword(fetchedUser.getId(), hashedPassword, db);
  EXPECT_TRUE(isPasswordCorrect);

  // Verify incorrect password
  bool isPasswordIncorrect = userManager->verifyPassword(fetchedUser.getId(), Utils::hashPassword("wrongpassword"), db);
  EXPECT_FALSE(isPasswordIncorrect);

  sqlite3_close(db);
}