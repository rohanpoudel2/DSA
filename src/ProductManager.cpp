#include "ProductManager.h"
#include <iostream>

// Written by Rohan Poudel
ProductManager::ProductManager(const std::string &filename) : Database(filename)
{
  createTable();
}

// Written by Rohan Poudel
void ProductManager::createTable()
{
  const char *createProductTableSQL = R"(
      CREATE TABLE IF NOT EXISTS products (
          id INTEGER PRIMARY KEY AUTOINCREMENT,
          name TEXT NOT NULL,
          price REAL NOT NULL,
          quantity INTEGER NOT NULL
      );
  )";

  char *errMsg = nullptr;
  if (sqlite3_exec(db, createProductTableSQL, nullptr, nullptr, &errMsg) != SQLITE_OK)
  {
    std::cerr << "Error creating products table: " << errMsg << std::endl;
    sqlite3_free(errMsg);
  }
}

// Written with AI Assistance (ChatGPT)
void ProductManager::saveProducts(const ProductList &productList, const std::string &mode)
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

  const char *sqlInsert = "INSERT INTO products (name, price, quantity) VALUES (?, ?, ?);";
  sqlite3_stmt *stmt;

  if (sqlite3_prepare_v2(db, sqlInsert, -1, &stmt, nullptr) != SQLITE_OK)
  {
    std::cerr << "Failed to prepare SQL statement: " << sqlite3_errmsg(db) << std::endl;
    return;
  }

  ProductList::Node *current = productList.getHead();
  while (current != nullptr)
  {
    sqlite3_bind_text(stmt, 1, current->product.getName().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_double(stmt, 2, current->product.getPrice());
    sqlite3_bind_int(stmt, 3, current->product.getQuantity());
    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
      std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
    }
    sqlite3_reset(stmt);
    current = current->next;
  }
  sqlite3_finalize(stmt);
}

// Written by Rohan Poudel
void ProductManager::loadProducts(ProductList &productList)
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