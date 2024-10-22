#ifndef PROMO_H
#define PROMO_H

#include <string>

class Promo
{
private:
  int promoId;
  int userId;
  int discountPercentage;
  std::string timestamp;

public:
  Promo(int promoId, int userId, int discountPercentage, const std::string &timestamp);

  // Getters
  int getPromoId() const;
  int getUserId() const;
  int getDiscountPercentage() const;
  std::string getTimestamp() const;

  // Setters
  void setPromoId(int id);
  void setUserId(int id);
  void setDiscountPercentage(int discount);
  void setTimestamp(const std::string &ts);
};

#endif // PROMO_H