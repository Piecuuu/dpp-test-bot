#include "event.h"
#include "config.h"
#include "logger.h"

namespace Bot {
void RegisterEvents(dpp::cluster& bot) {
  std::string SPACER = Config::config["spacer"].as<std::string>();
  int numOfRegistered = 0;
  Logger::debug("Registering Events...\n" + SPACER + "\n");
  for(auto& event : Events) {
    Logger::debug("Registering (event) " + event.first + "\n");
    event.second(bot);
    Logger::debug("Registered (event) " + event.first + "\n" + SPACER + "\n");
    numOfRegistered++;
  }
  Logger::debug(std::format("Registered Events: {}\n{}\n", numOfRegistered, SPACER));
}
}
