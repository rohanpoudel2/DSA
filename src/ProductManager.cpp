#include "ProductManager.h"
#include <iostream>

ProductManager::ProductManager(const std::string &filename) : Database(filename)
{
  db = connectToDB(sourceFile);
  if (db != nullptr)
  {
    createTables();
  }
}

void ProductManager::createTables()
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