#include "Menu.h"
#include "Utils.h"

std::string environment = "development";

// Written by Rohan Poudel
Menu::Menu()
    : userManager(Utils::getDatabasePath(environment)),
      productManager(Utils::getDatabasePath(environment)),
      inquiryManager(Utils::getDatabasePath(environment)),
      promoManager(Utils::getDatabasePath(environment)),
      inquiryQueue()
{
  Login();                                   // Begin with user login
  initializeMenuOptions();                   // Set up menu options based on user type
  productManager.loadProducts(productStack); // Load existing products into stack
}

// Written by Rohan Poudel
void Menu::initializeMenuOptions()
{
  // Initialize menu options for Admin or Customer based on their role
  if (currentUser.isAdmin())
  {
    admin_menu_options = {{{1, "Add new product", std::bind(&Menu::AddNewProduct, this)},
                           {2, "View all products", std::bind(&Menu::ViewAllProducts, this)},
                           {3, "Undo last added product", std::bind(&Menu::UndoLastAddedProduct, this)},
                           {4, "Process inquiry", std::bind(&Menu::ProcessInquiry, this)},
                           {5, "Exit", std::bind(&Menu::ExitMenu, this)}}};
  }
  else
  {
    customer_menu_options = {{{1, "Add new inquiry", std::bind(&Menu::AddNewInquiry, this)},
                              {2, "View inquiries", std::bind(&Menu::ViewInquiries, this)},
                              {3, "Spin Wheel for Promo", std::bind(&Menu::SpinWheel, this)},
                              {4, "Exit", std::bind(&Menu::ExitMenu, this)}}};
  }
}

// Written by Rohan Poudel
void Menu::displayMenu() const
{
  // Show the available menu options based on the role (Admin/Customer)
  std::cout << "===============================\n";
  std::cout << "       E-commerce Store\n";
  std::cout << "===============================\n";

  // Choose appropriate menu (admin/customer) based on user role
  const auto &menu = currentUser.isAdmin() ? admin_menu_options : customer_menu_options;

  for (const auto &option : menu)
  {
    std::cout << std::get<0>(option) << ". " << std::get<1>(option) << std::endl;
  }

  std::cout << "===============================\n";
  std::cout << "Enter your choice: ";
}

// Written with AI Assistance (ChatGPT)
void Menu::processOption() const
{
  // Process the menu option selected by the user
  int choice;
  std::cin >> choice;

  if (Utils::handleInputFailure(std::cin))
    return;

  // Select appropriate menu based on user role
  const auto &menu = currentUser.isAdmin() ? admin_menu_options : customer_menu_options;

  for (const auto &option : menu)
  {
    if (std::get<0>(option) == choice)
    {
      std::get<2>(option)(); // Execute the function bound to the menu option
      return;
    }
  }

  std::cout << "Invalid option!" << std::endl;
}

// Written by Rohan Poudel
void Menu::startMenu()
{
  // Keep the menu running until the user exits
  while (true)
  {
    displayMenu();
    processOption();
  }
}

// Written by Rohan Poudel
void Menu::Login()
{
  system("clear"); // Clear the screen on login
  std::string email, password;
  std::cout << "Welcome! Are you logging in as (1) Admin or (2) Customer? ";
  int roleOption;
  std::cin >> roleOption;

  // Handle login based on the user's selection
  if (roleOption == 1)
  {
    handleAdminLogin(password);
  }
  else
  {
    handleCustomerLogin(email, password);
  }
}

// Written by Rohan Poudel
void Menu::handleAdminLogin(std::string &password)
{
  // Admin login: check admin credentials
  Utils::promptForInput("Enter admin password: ", password);
  if (userManager.verifyPassword(1, Utils::hashPassword(password), userManager.getDB()))
  {
    currentUser = User("Admin", "rohan@poudel.com", "admin", password);
    std::cout << "Admin access granted!" << std::endl;
  }
  else
  {
    std::cerr << "Invalid admin credentials!" << std::endl;
    exit(1);
  }
}

// Written by Rohan Poudel
void Menu::handleCustomerLogin(std::string &email, std::string &password)
{
  // Customer login: validate email, then authenticate or register new user
  bool validEmail = false;
  while (!validEmail)
  {
    Utils::promptForInput("Enter your email: ", email);
    if (Utils::isValidEmail(email))
    {
      validEmail = true;
    }
    else
    {
      std::cerr << "Invalid email format. Please try again." << std::endl;
    }
  }

  currentUser = userManager.getCustomerByEmail(email, userManager.getDB());

  // Register new customer or authenticate existing one
  if (currentUser.getEmail().empty())
  {
    registerNewCustomer(email);
  }
  else
  {
    authenticateReturningCustomer(password);
  }
}

// Written by Rohan Poudel
void Menu::registerNewCustomer(const std::string &email)
{
  // Clear screen and register a new customer
  system("clear");
  std::string name, plainPassword;
  Utils::promptForInput("Enter your name: ", name);
  Utils::promptForInput("Enter your password: ", plainPassword);

  // Add new customer and allow them to spin the wheel for a discount
  currentUser = User(name, email, "customer", Utils::hashPassword(plainPassword));
  userManager.addUser(currentUser, userManager.getDB());
  std::cout << "Customer registered!" << std::endl;

  std::cout << "As a new customer, you get a chance to spin the wheel for a discount!" << std::endl;
  SpinWheel();
}

// Written by Rohan Poudel
void Menu::authenticateReturningCustomer(std::string &password)
{
  // Authenticate a returning customer by verifying password
  std::cout << "Welcome back, " << currentUser.getName() << "!" << std::endl;
  Utils::promptForInput("Enter your password: ", password);
  if (userManager.verifyPassword(1, Utils::hashPassword(password), userManager.getDB()))
  {
    std::cout << "Access granted!" << std::endl;
  }
  else
  {
    std::cerr << "Invalid credentials!" << std::endl;
    exit(1);
  }
}

// Written by Rohan Poudel
void Menu::AddNewProduct()
{
  system("clear");
  std::string product_name;
  double product_price;
  int product_quantity;

  // Gather input for new product details and save it
  Utils::promptForInput("Enter product name: ", product_name);
  Utils::promptForInput("Enter product price: ", product_price);
  Utils::promptForInput("Enter product quantity: ", product_quantity);

  Product newProduct(product_name, product_price, product_quantity);
  productStack.pushProduct(newProduct);
  productManager.saveProducts(productStack, "replace");

  std::cout << "Added new product: " << product_name << std::endl;
}

// Written by Rohan Poudel
void Menu::SpinWheel()
{
  system("clear");
  // Spin the wheel and check if the user already has a promo
  if (promoManager.userHasPromo(currentUser.getId()))
  {
    std::cout << "You already have a discount promo of: " << promoManager.getUserPromo(currentUser.getId()).getDiscountPercentage() << "%" << std::endl;
    return;
  }
  int discount = promoManager.spinWheel();
  std::cout << "Congratulations! You won a " << discount << "% discount on your next order!" << std::endl;

  // Save the promo in the database
  Promo promo(0, currentUser.getId(), discount, Utils::getCurrentTimestamp());
  promoManager.addPromo(promo);

  std::cout << "Your discount has been saved for future use!" << std::endl;
}

// Written by Rohan Poudel
void Menu::UndoLastAddedProduct()
{
  system("clear");
  // Undo the last product added to the stack
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

// Written by Rohan Poudel
void Menu::ViewAllProducts()
{
  // Display all the products currently available
  productStack.displayAllProducts();
}

// Written by Rohan Poudel
void Menu::AddNewInquiry()
{
  system("clear");
  std::string inquiryMessage;
  // Add a new inquiry to the system
  Utils::promptForInput("Enter your inquiry message: ", inquiryMessage);

  Inquiry inquiry(currentUser, inquiryMessage, "", Utils::getCurrentTimestamp());
  inquiryManager.saveInquiryToDB(inquiry);

  std::cout << "Inquiry added!" << std::endl;
}

// Written by Rohan Poudel
void Menu::ProcessInquiry()
{
  system("clear");
  bool continueProcessing = true;

  // Process each inquiry one by one until there are no more
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

// Written by Rohan Poudel
void Menu::ViewInquiries()
{
  system("clear");
  // View all inquiries for the current user
  inquiryQueue = inquiryManager.loadInquiriesForUser(currentUser.getId());
  if (inquiryQueue.isEmpty())
  {
    std::cout << "No inquiries found for your account." << std::endl;
    return;
  }

  inquiryQueue.displayAllInquiries();
}

// Written by Rohan Poudel
void Menu::ExitMenu()
{
  system("clear");
  std::cout << "Exiting..." << std::endl;
  exit(0);
}