#include "config.h"
#include <fstream>
#include <iostream>
#include "logger.h"

const std::string CONFIG_FILENAME = "config.yml";

namespace Config {
YAML::Node config;

YAML::Node loadConfig() {
  std::ifstream file(CONFIG_FILENAME);
  //if(!file.good()) throw std::runtime_error("Couldn't open 'config.yml'. File may be missing.");
  if(!file.good()) {
    createConfig();
    Logger::warn("Remember to check out the 'config.yml' before you start!\n");
    return loadConfig();
  }
  std::ostringstream sstr;
  sstr << file.rdbuf();
  std::string content = sstr.str();
  file.close();

  YAML::Node node = YAML::Load(content);
  config = node;
  return node;
}

void createConfig() {
  std::ofstream file(CONFIG_FILENAME);
  file << "token: \"YOUR_TOKEN_HERE\"\n";
  file << "colors:\n";
  file << "  neutral-blue: 0x0275bd\n";
  file << "  error-red: 0xbd021b\n";
  file << "  success-green: 0x56b300\n";
  file << "spacer: \"------------------------------------\"\n";
  file.close();
}
}
