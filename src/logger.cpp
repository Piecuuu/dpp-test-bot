#include "logger.h"
#include <format>
#include <iostream>

constexpr const char* str_end(const char *str) {
  return *str ? str_end(str + 1) : str;
}
constexpr bool str_slant(const char *str) {
  return *str == '/' ? true : (*str ? str_slant(str + 1) : false);
}
constexpr const char* r_slant(const char* str) {
  return *str == '/' ? (str + 1) : r_slant(str - 1);
}
constexpr const char* file_name(const char* str) {
  return str_slant(str) ? r_slant(str_end(str)) : str;
}

std::string Logger::base(const std::source_location location) {
  return std::format("{}({}:{}): ", file_name(location.file_name()), location.line(), location.column());
}
void Logger::log(std::string message, const std::source_location location) {
  std::cout << "[LOG] " << Logger::base(location) << message;
}
void Logger::error(std::string message, const std::source_location location) {
  std::cout << "[ERROR] " << Logger::base(location) << message;
}
void Logger::warn(std::string message, const std::source_location location) {
  std::cout << "[WARN] " << Logger::base(location) << message;
}
void Logger::debug(std::string message, const std::source_location location) {
  std::cout << "[DEBUG] " << Logger::base(location) << message;
}
