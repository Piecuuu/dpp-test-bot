#include "logger.h"
#include <format>
#include <iostream>
#include <ranges>

enum ColorList {
  Warn,
  Error,
  Debug,
  Log,
  Reset,
  Purple,
  Blue,
};

std::unordered_map<ColorList, std::string> Colors = {
  {Warn, "\e[0;33m"},
  {Error, "\e[0;31m"},
  {Debug, "\e[0;32m"},
  {Log, "\e[0;36m"},
  {Reset, "\e[0m"},
  {Purple, "\e[0;35m"},
  {Blue, "\e[0;34m"},
};

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
constexpr std::string get_last_split(const char* str, const char delim) {
  std::string fn = str;
  auto pos = fn.rfind(delim);
  return fn.substr(pos == fn.npos ? 0 : (pos + 1));
}
constexpr std::string get_first_split(const char* str, const char delim) {
  std::string fn = str;
  auto pos = fn.rfind(delim);
  return fn.substr(0, pos);
}

constexpr std::string extract_function_name_with_return_type(const char* function_name) {
  return get_first_split(function_name, '(');
}

constexpr std::string transformSignature(const std::string& signature) {
  std::size_t start = signature.find('(');
  std::size_t end = signature.find(')', start);

  if (start != std::string::npos && end != std::string::npos) {
    std::string result = static_cast<std::string>(std::string_view(signature.data(), start));
    result += std::string_view(signature.data() + end + 1, signature.size() - end - 1);
    if(result.find('(')) return transformSignature(result);
    return result;
  }

  return signature;
}
constexpr std::string extract_function_name(const char* function_name) {
  return get_last_split(transformSignature(std::string(function_name)).c_str(), ' ');
}


std::string Logger::base(const std::source_location location) {
  return std::format("{}{}{}({}{}{}:{}{}{}) [{}{}{}]: ",
    Colors[ColorList::Purple],
    file_name(location.file_name()),
    Colors[ColorList::Reset],

    Colors[ColorList::Error],
    location.line(),
    Colors[ColorList::Reset],

    Colors[ColorList::Warn],
    location.column(),
    Colors[ColorList::Reset],

    Colors[ColorList::Blue],
    extract_function_name(location.function_name()),
    Colors[ColorList::Reset]
  );
}
void Logger::log(std::string message, const std::source_location location) {
  std::cout << Colors[ColorList::Log] << "[LOG] " << Logger::base(location) << message;
}
void Logger::error(std::string message, const std::source_location location) {
  std::cerr << Colors[ColorList::Error] << "[ERROR] " << Logger::base(location) << message;
}
void Logger::warn(std::string message, const std::source_location location) {
  std::cerr << Colors[ColorList::Warn] << "[WARN] " << Logger::base(location) << message;
}
void Logger::debug(std::string message, const std::source_location location) {
  std::cout << Colors[ColorList::Debug] << "[DEBUG] " << Logger::base(location) << message;
}
