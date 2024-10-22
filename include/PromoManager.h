#ifndef PROMO_MANAGER_H
#define PROMO_MANAGER_H

#include "Database.h"
#include "Promo.h"
#include <list>

class PromoManager : public Database
{
public:
  PromoManager(const std::string &dbPath);
  ~PromoManager();

  void createTable();

  void addPromo(const Promo &promo);

  bool userHasPromo(int userId);

  Promo getUserPromo(int userId);

  int spinWheel();
};

#endif