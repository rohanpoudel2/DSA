#include "Menu.h"
#include "Utils.h"

std::string environment = "development";

std::string dbPath = Utils::getDatabasePath(environment);

Menu::Menu()
    : userManager("./data/store.db"),
      productManager("./data/store.db"),
      inquiryManager("./data/store.db"),
      promoManager("./data/store.db"),
      inquiryQueue()
{
  std::cout << dbPath << std::endl;
  Login();
  if (currentUser.isAdmin())
  {
    menu_options = {{{1, "Add new product", std::bind(&Menu::AddNewProduct, this)},
                     {2, "View all products", std::bind(&Menu::ViewAllProducts, this)},
                     {3, "Undo last added product", std::bind(&Menu::UndoLastAddedProduct, this)},
                     {4, "Process inquiry", std::bind(&Menu::ProcessInquiry, this)},
                     {5, "Exit", std::bind(&Menu::ExitMenu, this)}}};
  }
  else
  {
    menu_options = {{{1, "Add new inquiry", std::bind(&Menu::AddNewInquiry, this)},
                     {2, "View inquiries", std::bind(&Menu::ViewInquiries, this)},
                     {3, "Spin Wheel for Promo", std::bind(&Menu::SpinWheel, this)},
                     {4, "Exit", std::bind(&Menu::ExitMenu, this)}}};
  }

  productManager.loadProducts(productStack);
}

void Menu::displayMenu() const
{
  std::cout << "===============================" << std::endl;
  std::cout << "       E-commerce Store" << std::endl;
  std::cout << "===============================" << std::endl;
  for (const auto &option : menu_options)
  {
    std::cout << std::get<0>(option) << ". " << std::get<1>(option) << std::endl;
  }
  std::cout << "===============================" << std::endl;
  std::cout << "Enter your choice: ";
}

void Menu::processOption() const
{
  int choice;
  std::cin >> choice;

  if (Utils::handleInputFailure(std::cin))
    return;

  for (const auto &option : menu_options)
  {
    if (std::get<0>(option) == choice)
    {
      std::get<2>(option)();
      return;
    }
  }

  std::cout << "Invalid option!" << std::endl;
}

void Menu::startMenu()
{
  while (true)
  {
    displayMenu();
    processOption();
  }
}

void Menu::Login()
{
  std::string email, password;
  std::cout << "Welcome! Are you logging in as (1) Admin or (2) Customer? ";
  int roleOption;
  std::cin >> roleOption;

  if (roleOption == 1)
  {
    Utils::promptForInput("Enter admin password: ", password);
    if (userManager.verifyAdminPassword(Utils::hashPassword(password), userManager.getDB()))
    {
      currentUser = User("Admin", "admin@store.com", "admin", password);
      std::cout << "Admin access granted!" << std::endl;
    }
    else
    {
      std::cerr << "Invalid admin credentials!" << std::endl;
      exit(1);
    }
  }
  else
  {
    Utils::promptForInput("Enter your email: ", email);
    currentUser = userManager.getCustomerByEmail(email, userManager.getDB());

    if (currentUser.getEmail().empty())
    {
      std::string name;
      Utils::promptForInput("Enter your name: ", name);
      std::string plainPassword;
      Utils::promptForInput("Enter your password: ", plainPassword);

      currentUser = User(name, email, "customer", Utils::hashPassword(plainPassword));
      userManager.addUser(currentUser, userManager.getDB());
      std::cout << "Customer registered!" << std::endl;

      std::cout << "As a new customer, you get a chance to spin the wheel for a discount!" << std::endl;
      SpinWheel();
    }
    else
    {
      std::cout << "Welcome back, " << currentUser.getName() << "!" << std::endl;
    }
  }
}

void Menu::AddNewProduct()
{
  std::string product_name;
  double product_price;
  int product_quantity;

  Utils::promptForInput("Enter product name: ", product_name);
  Utils::promptForInput("Enter product price: ", product_price);
  Utils::promptForInput("Enter product quantity: ", product_quantity);

  Product newProduct(product_name, product_price, product_quantity);
  productStack.pushProduct(newProduct);
  productManager.saveProducts(productStack, "replace");

  std::cout << "Added new product: " << product_name << std::endl;
}

void Menu::SpinWheel()
{
  int discount = promoManager.spinWheel();
  std::cout << "Congratulations! You won a " << discount << "% discount on your next order!" << std::endl;

  Promo promo(0, currentUser.getId(), discount, Utils::getCurrentTimestamp());
  promoManager.addPromo(promo);

  std::cout << "Your discount has been saved for future use!" << std::endl;
}

void Menu::UndoLastAddedProduct()
{
  if (!productStack.isEmpty())
  {
    Product removedProduct = productStack.popProduct();
    std::cout << "Undoing the last added product: " << removedProduct.getName() << std::endl;
    productManager.saveProducts(productStack, "replace");
  }
  else
  {
    std::cout << "No products to undo!" << std::endl;
  }
}

void Menu::ViewAllProducts()
{
  productStack.displayAllProducts();
}

void Menu::AddNewInquiry()
{
  std::string inquiryMessage;
  Utils::promptForInput("Enter your inquiry message: ", inquiryMessage);

  Inquiry inquiry(currentUser, inquiryMessage, Utils::getCurrentTimestamp());
  inquiryManager.saveInquiryToDB(inquiry);

  std::cout << "Inquiry added!" << std::endl;
}

void Menu::ProcessInquiry()
{
  bool continueProcessing = true;

  InquiryQueue inquiryQueue = inquiryManager.loadAllInquiriesWithNoResponses();

  while (continueProcessing)
  {
    if (inquiryQueue.isEmpty())
    {
      std::cout << "No more inquiries to process.\n";
      return;
    }

    Inquiry inquiry = inquiryQueue.peekFront();

    std::cout << "Inquiry from: " << inquiry.getUser().getName() << " ("
              << inquiry.getUser().getEmail() << ")\n";
    std::cout << "Message: " << inquiry.getMessage() << "\n";
    std::cout << "Timestamp: " << inquiry.getTimestamp() << "\n";

    std::string response;
    Utils::promptForInput("Enter your response: ", response);

    inquiry.setResponse(response);
    inquiryManager.saveInquiryResponseToDB(inquiry);

    std::cout << "Response saved.\n";

    inquiryQueue.dequeue();

    char choice;
    std::cout << "Do you want to process the next inquiry? (y/n): ";
    std::cin >> choice;

    if (choice != 'y' && choice != 'Y')
    {
      continueProcessing = false;
    }
  }
}

void Menu::ViewInquiries()
{
  inquiryQueue = inquiryManager.loadInquiriesForUser(currentUser.getId());
  if (inquiryQueue.isEmpty())
  {
    std::cout << "No inquiries found for your account." << std::endl;
    return;
  }

  inquiryQueue.displayAllInquiries();
}

void Menu::ExitMenu()
{
  std::cout << "Exiting..." << std::endl;
  exit(0);
}