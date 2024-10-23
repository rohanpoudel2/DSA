#ifndef INQUIRY_MANAGER_H
#define INQUIRY_MANAGER_H

#include "Database.h"
#include "User.h"
#include "InquiryQueue.h"

class InquiryManager : public Database
{
public:
  // Constructor for InquiryManager
  // Precondition: A valid database filename must be passed.
  // Postcondition: InquiryManager object is created, and the database connection is established.
  InquiryManager(const std::string &filename);

  // Creates the inquiries table if it doesn't exist in the database.
  // Precondition: Database connection must be valid.
  // Postcondition: The inquiries table is created in the database if not already present.
  void createTable();

  // Saves a new inquiry to the database.
  // Precondition: The Inquiry object must be valid and contain user information and a message.
  // Postcondition: Inquiry is stored in the database.
  void saveInquiryToDB(const Inquiry &inquiry);

  // Loads all inquiries associated with a specific user.
  // Precondition: The userId must be valid and exist in the users' table.
  // Postcondition: Returns an InquiryQueue with all inquiries related to the user.
  InquiryQueue loadInquiriesForUser(int userId);

  // Loads all inquiries that have not received a response.
  // Precondition: Database connection must be valid.
  // Postcondition: Returns an InquiryQueue with all inquiries that do not have a response.
  InquiryQueue loadAllInquiriesWithNoResponses();

  // Removes an inquiry from the database by inquiryId.
  // Precondition: The inquiryId must correspond to a valid inquiry in the database.
  // Postcondition: The inquiry is removed from the database.
  void removeInquiryFromDB(int inquiryId);

  // Updates an inquiry with a response and saves it to the database.
  // Precondition: The Inquiry object must have a valid response.
  // Postcondition: The inquiry in the database is updated with the response.
  void saveInquiryResponseToDB(const Inquiry &inquiry);
};

#endif