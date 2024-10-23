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
  // Constructor to initialize Promo object
  // Precondition: promoId, userId, and discountPercentage should be valid integers, and timestamp should be a valid string.
  // Postcondition: Promo object is created with the given parameters.
  Promo(int promoId, int userId, int discountPercentage, const std::string &timestamp);

  // Getter for promoId
  // Precondition: None.
  // Postcondition: Returns the unique identifier (promoId) of the promo.
  int getPromoId() const;

  // Getter for userId
  // Precondition: None.
  // Postcondition: Returns the userId associated with the promo.
  int getUserId() const;

  // Getter for discountPercentage
  // Precondition: None.
  // Postcondition: Returns the discount percentage of the promo.
  int getDiscountPercentage() const;

  // Getter for timestamp
  // Precondition: None.
  // Postcondition: Returns the timestamp when the promo was created.
  std::string getTimestamp() const;

  // Setter for promoId
  // Precondition: id should be a valid integer.
  // Postcondition: Sets the promoId to the provided value.
  void setPromoId(int id);

  // Setter for userId
  // Precondition: id should be a valid integer.
  // Postcondition: Sets the userId to the provided value.
  void setUserId(int id);

  // Setter for discountPercentage
  // Precondition: discount should be a valid integer representing the discount percentage.
  // Postcondition: Sets the discountPercentage to the provided value.
  void setDiscountPercentage(int discount);

  // Setter for timestamp
  // Precondition: ts should be a valid string representing the timestamp.
  // Postcondition: Sets the timestamp to the provided value.
  void setTimestamp(const std::string &ts);
};

#endif