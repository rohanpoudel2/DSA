#include "Promo.h"

Promo::Promo(int promoId, int userId, int discountPercentage, const std::string &timestamp)
    : promoId(promoId), userId(userId), discountPercentage(discountPercentage), timestamp(timestamp) {}

int Promo::getPromoId() const { return promoId; }
int Promo::getUserId() const { return userId; }
int Promo::getDiscountPercentage() const { return discountPercentage; }
std::string Promo::getTimestamp() const { return timestamp; }

void Promo::setPromoId(int id) { promoId = id; }
void Promo::setUserId(int id) { userId = id; }
void Promo::setDiscountPercentage(int discount) { discountPercentage = discount; }
void Promo::setTimestamp(const std::string &ts) { timestamp = ts; }