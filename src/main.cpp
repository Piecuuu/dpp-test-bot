#include <dpp/dpp.h>
#include "config.h"
#include "slash.h"
#include "bot.h"

int main() {
  YAML::Node config = Config::loadConfig();
  std::string token = config["token"].as<std::string>();

  Bot::startBot(token);
  delete Bot::CBot::bot;
  return 0;
}
