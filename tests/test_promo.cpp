#include <gtest/gtest.h>
#include "Promo.h"

// Test the parameterized constructor and getters
TEST(PromoTest, ParameterizedConstructorAndGetters)
{
  int promoId = 101;
  int userId = 202;
  int discountPercentage = 15;
  std::string timestamp = "2023-10-20 12:34:56";

  // Create a Promo object using the parameterized constructor
  Promo promo(promoId, userId, discountPercentage, timestamp);

  // Test getters
  EXPECT_EQ(promo.getPromoId(), promoId);
  EXPECT_EQ(promo.getUserId(), userId);
  EXPECT_EQ(promo.getDiscountPercentage(), discountPercentage);
  EXPECT_EQ(promo.getTimestamp(), timestamp);
}

// Test setters
TEST(PromoTest, SettersAndGetters)
{
  Promo promo(0, 0, 0, "");

  // Set new values using setters
  promo.setPromoId(103);
  promo.setUserId(203);
  promo.setDiscountPercentage(20);
  promo.setTimestamp("2023-11-01 14:22:33");

  // Test if the getters return the newly set values
  EXPECT_EQ(promo.getPromoId(), 103);
  EXPECT_EQ(promo.getUserId(), 203);
  EXPECT_EQ(promo.getDiscountPercentage(), 20);
  EXPECT_EQ(promo.getTimestamp(), "2023-11-01 14:22:33");
}