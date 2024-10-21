#include "User.h"

// Default constructor
User::User() : id(0), name(""), email(""), role("customer"), password("") {}

// Parameterized constructor
User::User(const std::string &name, const std::string &email, const std::string &role, const std::string &password)
    : name(name), email(email), role(role), password(password) {}

int User::getId() const { return id; }
std::string User::getName() const { return name; }
std::string User::getEmail() const { return email; }
std::string User::getRole() const { return role; }
std::string User::getPassword() const { return password; }

void User::setId(int id) { this->id = id; }
void User::setName(const std::string &name) { this->name = name; }
void User::setEmail(const std::string &email) { this->email = email; }
void User::setRole(const std::string &role) { this->role = role; }
void User::setPassword(const std::string &password) { this->password = password; }

User User::getUserById(int userId, sqlite3 *db)
{
    User user;
    const char *sql = "SELECT id, name, email, role FROM users WHERE id=?;";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK)
    {
        sqlite3_bind_int(stmt, 1, userId);

        if (sqlite3_step(stmt) == SQLITE_ROW)
        {
            int id = sqlite3_column_int(stmt, 0);
            std::string name = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
            std::string email = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
            std::string role = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3));

            // Create and return the User object
            user = User(name, email, role, "");
            user.setId(id);
        }
    }
    sqlite3_finalize(stmt);
    return user;
}

bool User::isAdmin() const { return role == "admin"; }