#ifndef LOGGER_H
#define LOGGER_H

#include <source_location>
#include <string>
#include <unordered_map>

class Logger {
  public:
    static std::string base(const std::source_location location);
    static void log(std::string message, const std::source_location location = std::source_location::current());
    static void debug(std::string message, const std::source_location location = std::source_location::current());
    static void warn(std::string message, const std::source_location location = std::source_location::current());
    static void error(std::string message, const std::source_location location = std::source_location::current());
};
#endif
