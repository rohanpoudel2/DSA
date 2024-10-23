#include "Promo.h"

// Written by Rohan Poudel
Promo::Promo(int promoId, int userId, int discountPercentage, const std::string &timestamp)
    : promoId(promoId), userId(userId), discountPercentage(discountPercentage), timestamp(timestamp) {}

// Written by Rohan Poudel
int Promo::getPromoId() const { return promoId; }

// Written by Rohan Poudel
int Promo::getUserId() const { return userId; }

// Written by Rohan Poudel
int Promo::getDiscountPercentage() const { return discountPercentage; }

// Written by Rohan Poudel
std::string Promo::getTimestamp() const { return timestamp; }

// Written by Rohan Poudel
void Promo::setPromoId(int id) { promoId = id; }

// Written by Rohan Poudel
void Promo::setUserId(int id) { userId = id; }

// Written by Rohan Poudel
void Promo::setDiscountPercentage(int discount) { discountPercentage = discount; }

// Written by Rohan Poudel
void Promo::setTimestamp(const std::string &ts) { timestamp = ts; }