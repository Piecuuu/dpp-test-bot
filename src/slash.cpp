#include "slash.h"
#include "config.h"

namespace Bot {
void RegisterCommands(dpp::cluster& bot) {
  std::string SPACER = Config::config["spacer"].as<std::string>();
  int numOfRegistered = 0;
  std::cout << "Registering Commands...\n" << SPACER << "\n";
  for(auto& command : Commands) {
    std::cout << "Registering (command) " << command.first << "\n";
    command.second.registerFunc(bot);
    std::cout << "Registered (command) " << command.first << "\n" << SPACER << "\n";
    numOfRegistered++;
  }
  std::cout << "Registered Commands: " << numOfRegistered << "\n" << SPACER << "\n";
}
}
