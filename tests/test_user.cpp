#include <gtest/gtest.h>
#include "User.h"
#include <sqlite3.h>

// Test default constructor and getters
TEST(UserTest, DefaultConstructor)
{
  User user;

  EXPECT_EQ(user.getId(), 0);
  EXPECT_EQ(user.getName(), "");
  EXPECT_EQ(user.getEmail(), "");
  EXPECT_EQ(user.getRole(), "customer");
  EXPECT_EQ(user.getPassword(), "");
  EXPECT_FALSE(user.isAdmin());
}

// Test parameterized constructor and getters
TEST(UserTest, ParameterizedConstructor)
{
  User user("Rohan", "rohan@example.com", "admin", "hashedpassword");

  EXPECT_EQ(user.getName(), "Rohan");
  EXPECT_EQ(user.getEmail(), "rohan@example.com");
  EXPECT_EQ(user.getRole(), "admin");
  EXPECT_EQ(user.getPassword(), "hashedpassword");
  EXPECT_TRUE(user.isAdmin());
}

// Test setters and getters
TEST(UserTest, SettersAndGetters)
{
  User user;

  user.setId(1);
  user.setName("Alice");
  user.setEmail("alice@example.com");
  user.setRole("customer");
  user.setPassword("secret");

  EXPECT_EQ(user.getId(), 1);
  EXPECT_EQ(user.getName(), "Alice");
  EXPECT_EQ(user.getEmail(), "alice@example.com");
  EXPECT_EQ(user.getRole(), "customer");
  EXPECT_EQ(user.getPassword(), "secret");
  EXPECT_FALSE(user.isAdmin()); // Role is "customer", so not an admin
}

// Test isAdmin method
TEST(UserTest, IsAdmin)
{
  User adminUser("Admin", "admin@example.com", "admin", "hashedpassword");
  EXPECT_TRUE(adminUser.isAdmin());

  User customerUser("Customer", "customer@example.com", "customer", "hashedpassword");
  EXPECT_FALSE(customerUser.isAdmin());
}

// Test retrieving user by ID from the database
TEST(UserTest, GetUserById)
{
  // Initialize the database
  sqlite3 *db;
  sqlite3_open(":memory:", &db); // Use an in-memory database for testing

  // Create the users table
  const char *createUserTableSQL = R"(
        CREATE TABLE users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL,
            email TEXT NOT NULL UNIQUE,
            role TEXT NOT NULL,
            password TEXT NOT NULL
        );
    )";
  sqlite3_exec(db, createUserTableSQL, nullptr, nullptr, nullptr);

  // Insert a test user into the database
  const char *insertUserSQL = R"(
        INSERT INTO users (name, email, role, password) 
        VALUES ('John Doe', 'john@example.com', 'admin', 'hashedpassword');
    )";
  sqlite3_exec(db, insertUserSQL, nullptr, nullptr, nullptr);

  // Retrieve the user by ID
  User user = User::getUserById(1, db);

  // Verify the retrieved user details
  EXPECT_EQ(user.getId(), 1);
  EXPECT_EQ(user.getName(), "John Doe");
  EXPECT_EQ(user.getEmail(), "john@example.com");
  EXPECT_EQ(user.getRole(), "admin");

  sqlite3_close(db);
}