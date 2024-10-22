#ifndef INQUIRY_MANAGER_H
#define INQUIRY_MANAGER_H

#include "Database.h"
#include "User.h"
#include "InquiryQueue.h"

class InquiryManager : public Database
{
public:
  InquiryManager(const std::string &filename);
  void createTable();

  void saveInquiryToDB(const Inquiry &inquiry);
  InquiryQueue loadInquiriesForUser(int userId);
  InquiryQueue loadAllInquiriesWithNoResponses();
  void removeInquiryFromDB(int inquiryId);
  void saveInquiryResponseToDB(const Inquiry &inquiry);
};

#endif
