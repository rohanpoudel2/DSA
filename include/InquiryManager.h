#ifndef INQUIRY_MANAGER_H
#define INQUIRY_MANAGER_H

#include "Database.h"
#include "InquiryQueue.h"

class InquiryManager : public Database
{
public:
  InquiryManager(const std::string &filename);
  void createTables() override;

  // Inquiry-specific operations
  void saveInquiryToDB(const InquiryNode &inquiry, int user_id);
  InquiryNode *loadNextInquiryFromDB();
  void removeInquiryFromDB(int inquiry_id);
};

#endif