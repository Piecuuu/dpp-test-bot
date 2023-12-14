#include "event.h"
#include "config.h"

namespace Bot {
void RegisterEvents(dpp::cluster& bot) {
  std::string SPACER = Config::config["spacer"].as<std::string>();
  int numOfRegistered = 0;
  std::cout << "Registering Events...\n" << SPACER << "\n";
  for(auto& event : Events) {
    std::cout << "Registering (event) " << event.first << "\n";
    event.second(bot);
    std::cout << "Registered (event) " << event.first << "\n" << SPACER << "\n";
    numOfRegistered++;
  }
  std::cout << "Registered Events: " << numOfRegistered << "\n" << SPACER << "\n";
}
}
