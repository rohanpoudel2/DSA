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
private:
  std::vector<std::tuple<int, std::string, std::function<void()>>> admin_menu_options;
  std::vector<std::tuple<int, std::string, std::function<void()>>> customer_menu_options;

  UserManager userManager;
  ProductManager productManager;
  InquiryManager inquiryManager;
  InquiryQueue inquiryQueue;
  PromoManager promoManager;

  User currentUser;
  ProductList productStack;

  std::string dbPath;

  void initializeMenuOptions();
  void handleAdminLogin(std::string &password);
  void handleCustomerLogin(std::string &email, std::string &password);
  void registerNewCustomer(const std::string &email);
  void authenticateReturningCustomer(std::string &password);

public:
  Menu();

  void displayMenu() const;
  void processOption() const;
  void startMenu();
  void Login();

  // Admin functions
  void AddNewProduct();
  void ViewAllProducts();
  void UndoLastAddedProduct();

  // Customer functions
  void AddNewInquiry();
  void ProcessInquiry();
  void ViewInquiries();

  std::string getDbPath() const { return dbPath; }
  void setDbPath(const std::string &path) { dbPath = path; }

  void SpinWheel();

  void ExitMenu();
};

#endif