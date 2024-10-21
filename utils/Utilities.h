#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>
#include <functional>

inline std::string hashPassword(const std::string &password)
{
  std::hash<std::string> hasher;
  return std::to_string(hasher(password));
}

#endif