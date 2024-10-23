#ifndef PROMO_MANAGER_H
#define PROMO_MANAGER_H

#include "Database.h"
#include "Promo.h"
#include <list>

class PromoManager : public Database
{
public:
  // Constructor: Initializes PromoManager with the given database path.
  // Precondition: dbPath must be a valid string representing the path to the database file.
  // Postcondition: PromoManager object is initialized, and the database connection is established.
  PromoManager(const std::string &dbPath);

  // Destructor: Closes the database connection if it's open.
  // Precondition: The PromoManager object must have a valid database connection.
  // Postcondition: The database connection is closed.
  ~PromoManager();

  // Creates the 'promos' table if it doesn't exist.
  // Precondition: The database must be connected.
  // Postcondition: The 'promos' table is created in the database if it does not already exist.
  void createTable();

  // Adds a promo to the 'promos' table.
  // Precondition: promo must be a valid Promo object.
  // Postcondition: The promo is inserted into the 'promos' table in the database.
  void addPromo(const Promo &promo);

  // Checks if the user has a promo available.
  // Precondition: userId must be a valid integer representing a user in the database.
  // Postcondition: Returns true if the user has a promo, false otherwise.
  bool userHasPromo(int userId);

  // Retrieves the promo details for the specified user.
  // Precondition: userId must be a valid integer representing a user in the database.
  // Postcondition: Returns the Promo object associated with the user.
  Promo getUserPromo(int userId);

  // Spins the wheel and returns a discount percentage.
  // Precondition: None.
  // Postcondition: Returns a random discount percentage from the available options.
  int spinWheel();
};

#endif