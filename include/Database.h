#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <sqlite3.h>
#include "Product.h"
#include "ProductList.h"
#include "InquiryQueue.h"
#include "User.h"
#include "../utils/Utilities.h"

class Database
{
private:
  std::string sourceFile; // The source path where the database file will be saved
  sqlite3 *db;            // SQLite3 database connection handle

public:
  // Constructor
  Database(const std::string &filename);

  // Destructor to close the database connection
  ~Database();

  // Connect to SQLite Database
  sqlite3 *connectToDB(const std::string &dbPath);

  // Create necessary tables
  void createTables(sqlite3 *db);

  // User-related functions
  bool verifyAdminPassword(const std::string &hashedPassword);
  void addUser(const User &user);
  User getCustomerByEmail(const std::string &email);

  // Product-related functions
  void saveProducts(const ProductList &productList, const std::string &mode = "append");
  void loadProducts(ProductList &productList);

  // Inquiry-related functions
  void saveInquiryToDB(const InquiryNode &inquiry, int user_id);
  InquiryNode *loadNextInquiryFromDB();
  void removeInquiryFromDB(int inquiry_id);
};

#endif