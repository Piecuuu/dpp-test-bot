#include "slash.h"

namespace Bot {
void RegisterCommands(dpp::cluster& bot) {
  Bot::PingCommand::registerCommand(bot);
  Bot::HelloCommand::registerCommand(bot);
}
}
