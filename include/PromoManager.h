#ifndef PROMO_MANAGER_H
#define PROMO_MANAGER_H

#include "Promo.h"
#include <sqlite3.h>
#include <list>

class PromoManager
{
private:
  sqlite3 *db;

public:
  PromoManager(const std::string &dbPath);
  ~PromoManager();

  void createPromoTable();

  void addPromo(const Promo &promo);

  bool userHasPromo(int userId);

  Promo getUserPromo(int userId);

  int spinWheel();
};

#endif