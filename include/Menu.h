#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <array>
#include <functional>
#include <tuple>
#include "UserManager.h"
#include "ProductManager.h"
#include "InquiryManager.h"
#include "InquiryQueue.h"
#include "User.h"
#include "ProductList.h"
#include "PromoManager.h"

class Menu
{
private:
  std::array<std::tuple<int, std::string, std::function<void()>>, 6> menu_options;

  UserManager userManager;
  ProductManager productManager;
  InquiryManager inquiryManager;
  InquiryQueue inquiryQueue;
  PromoManager promoManager;

  User currentUser;
  ProductList productStack;

  std::string dbPath;

public:
  Menu();

  void displayMenu() const;

  void processOption() const;

  void startMenu();

  void Login();

  void AddNewProduct();
  void ViewAllProducts();
  void UndoLastAddedProduct();

  void AddNewInquiry();
  void ProcessInquiry();
  void ViewInquiries();

  std::string getDbPath() const { return dbPath; }

  void setDbPath(const std::string &path) { dbPath = path; }

  void SpinWheel();

  void ExitMenu();
};

#endif