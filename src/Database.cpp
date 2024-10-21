#include "Database.h"
#include "InquiryQueue.h"
#include <sqlite3.h>
#include <iostream>
#include <sstream>

// Constructor initializes the database with the given file path
Database::Database(const std::string &filename) : sourceFile(filename)
{
  db = connectToDB(sourceFile);
  if (db != nullptr)
  {
    createTables(db); // Ensure necessary tables are created
  }
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

// Create tables if they do not exist
void Database::createTables(sqlite3 *db)
{
  const char *createProductTableSQL = R"(
        CREATE TABLE IF NOT EXISTS products (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL,
            price REAL NOT NULL,
            quantity INTEGER NOT NULL
        );
    )";

  const char *createUserTableSQL = R"(
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL,
            email TEXT NOT NULL UNIQUE,
            role TEXT NOT NULL,
            password TEXT NOT NULL
        );
    )";

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
  if (sqlite3_exec(db, createProductTableSQL, nullptr, nullptr, &errMsg) != SQLITE_OK)
  {
    std::cerr << "Error creating products table: " << errMsg << std::endl;
    sqlite3_free(errMsg);
  }

  if (sqlite3_exec(db, createUserTableSQL, nullptr, nullptr, &errMsg) != SQLITE_OK)
  {
    std::cerr << "Error creating users table: " << errMsg << std::endl;
    sqlite3_free(errMsg);
  }

  if (sqlite3_exec(db, createInquiryTableSQL, nullptr, nullptr, &errMsg) != SQLITE_OK)
  {
    std::cerr << "Error creating inquiries table: " << errMsg << std::endl;
    sqlite3_free(errMsg);
  }

  // Automatically create the root user with password "root" if it doesn't already exist
  const char *checkAdminSQL = "SELECT COUNT(*) FROM users WHERE role = 'admin';";
  sqlite3_stmt *stmt;
  if (sqlite3_prepare_v2(db, checkAdminSQL, -1, &stmt, nullptr) == SQLITE_OK)
  {
    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
      int adminCount = sqlite3_column_int(stmt, 0);
      if (adminCount == 0)
      {
        // No admin exists, insert the root user
        const char *insertRootSQL = "INSERT INTO users (name, email, role, password) VALUES (?, ?, ?, ?);";
        sqlite3_stmt *insertStmt;
        if (sqlite3_prepare_v2(db, insertRootSQL, -1, &insertStmt, nullptr) == SQLITE_OK)
        {
          std::string rootPassword = "root";
          std::string hashedPassword = hashPassword(rootPassword); // Hash the root password

          sqlite3_bind_text(insertStmt, 1, "Root User", -1, SQLITE_STATIC);
          sqlite3_bind_text(insertStmt, 2, "admin@store.com", -1, SQLITE_STATIC);
          sqlite3_bind_text(insertStmt, 3, "admin", -1, SQLITE_STATIC);
          sqlite3_bind_text(insertStmt, 4, hashedPassword.c_str(), -1, SQLITE_STATIC);

          if (sqlite3_step(insertStmt) != SQLITE_DONE)
          {
            std::cerr << "Error inserting root user: " << sqlite3_errmsg(db) << std::endl;
          }
          sqlite3_finalize(insertStmt);
        }
      }
    }
  }
}

// Verify the admin password
bool Database::verifyAdminPassword(const std::string &hashedPassword)
{
  sqlite3_stmt *stmt;
  const char *sql = "SELECT password FROM users WHERE role='admin';";
  bool verified = false;

  if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK)
  {
    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
      std::string storedHash = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
      verified = (storedHash == hashedPassword);
    }
  }
  sqlite3_finalize(stmt);
  return verified;
}

// Add a new user to the database
void Database::addUser(const User &user)
{
  const char *sql = "INSERT INTO users (name, email, role, password) VALUES (?,?,?,?);";
  sqlite3_stmt *stmt;

  if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK)
  {
    sqlite3_bind_text(stmt, 1, user.getName().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, user.getEmail().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, user.getRole().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, user.getPassword().c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
      std::cerr << "Error inserting user: " << sqlite3_errmsg(db) << std::endl;
    }
  }
  sqlite3_finalize(stmt);
}

// Fetch a customer by email
User Database::getCustomerByEmail(const std::string &email)
{
  const char *sql = "SELECT id, name, email, role, password FROM users WHERE email=?;";
  sqlite3_stmt *stmt;
  User user;

  if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK)
  {
    sqlite3_bind_text(stmt, 1, email.c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
      int id = sqlite3_column_int(stmt, 0);
      std::string name = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
      std::string userEmail = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
      std::string role = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3));
      std::string password = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 4));

      user = User(name, userEmail, role, password);
      user.setId(id);
    }
  }
  sqlite3_finalize(stmt);
  return user;
}

// Save product list to the database
void Database::saveProducts(const ProductList &productList, const std::string &mode)
{
  if (mode == "replace")
  {
    const char *sqlClear = "DELETE FROM products;";
    char *errMsg = nullptr;
    if (sqlite3_exec(db, sqlClear, nullptr, nullptr, &errMsg) != SQLITE_OK)
    {
      std::cerr << "SQL error: " << errMsg << std::endl;
      sqlite3_free(errMsg);
    }
  }

  ProductList::Node *current = productList.getHead();
  while (current != nullptr)
  {
    std::string sqlInsert = "INSERT INTO products (name, price, quantity) VALUES ('" +
                            current->product.getName() + "', " +
                            std::to_string(current->product.getPrice()) + ", " +
                            std::to_string(current->product.getQuantity()) + ");";

    char *errMsg = nullptr;
    if (sqlite3_exec(db, sqlInsert.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK)
    {
      std::cerr << "SQL error: " << errMsg << std::endl;
      sqlite3_free(errMsg);
    }
    current = current->next;
  }
}

// Load products from the database into the product list
void Database::loadProducts(ProductList &productList)
{
  productList.clear();

  const char *sqlSelect = "SELECT name, price, quantity FROM products ORDER BY rowid DESC;";
  sqlite3_stmt *stmt;

  if (sqlite3_prepare_v2(db, sqlSelect, -1, &stmt, nullptr) == SQLITE_OK)
  {
    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
      std::string name = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
      double price = sqlite3_column_double(stmt, 1);
      int quantity = sqlite3_column_int(stmt, 2);

      Product product(name, price, quantity);
      productList.pushProduct(product);
    }
  }
  else
  {
    std::cerr << "Failed to fetch products: " << sqlite3_errmsg(db) << std::endl;
  }

  sqlite3_finalize(stmt);
}

// Save an inquiry to the database
void Database::saveInquiryToDB(const InquiryNode &inquiry, int user_id)
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
InquiryNode *Database::loadNextInquiryFromDB()
{
  const char *sql = "SELECT inquiry_id, inquiry_message FROM inquiries ORDER BY inquiry_timestamp ASC LIMIT 1;";
  sqlite3_stmt *stmt;
  InquiryNode *inquiry = nullptr;

  if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK)
  {
    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
      inquiry = new InquiryNode("", "", reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1)));

      int inquiry_id = sqlite3_column_int(stmt, 0);
      removeInquiryFromDB(inquiry_id); // Remove inquiry after processing
    }
  }

  sqlite3_finalize(stmt);
  return inquiry;
}

// Remove inquiry after processing
void Database::removeInquiryFromDB(int inquiry_id)
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