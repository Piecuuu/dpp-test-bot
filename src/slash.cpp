#include "slash.h"
#include "config.h"
#include "logger.h"

namespace Bot {
void RegisterCommands(dpp::cluster& bot) {
  std::string SPACER = Config::config["spacer"].as<std::string>();
  int numOfRegistered = 0;
  Logger::debug("Registering Commands...\n" + SPACER + "\n");
  for(auto& command : Commands) {
    Logger::debug("Registering (command) " + command.first + "\n");
    command.second.registerFunc(bot);
    Logger::debug("Registered (command) " + command.first + "\n" + SPACER + "\n");
    numOfRegistered++;
  }
  Logger::debug(std::format("Registered Commands: {}\n{}\n", numOfRegistered, SPACER));
}
}
