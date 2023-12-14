#include "bot.h"
#include "slash.h"
#include "event.h"

namespace Bot {
dpp::cluster* CBot::bot = nullptr;
dpp::cluster& startBot(std::string token) {
  CBot botobj;
  botobj.create(token);
  dpp::cluster& bot = *CBot::bot;

  //bot.on_log(dpp::utility::cout_logger());

  /*bot.on_slashcommand([](const dpp::slashcommand_t& event) {
    std::string cmd = event.command.get_command_name();
    auto it = Commands.find(cmd);
    //assert(it == Commands.end());
    it->second(event);
  });*/

  Bot::RegisterEvents(bot);

  /*bot.on_ready([&bot](const dpp::ready_t& event) {
    if (dpp::run_once<struct register_bot_commands>()) {
      Bot::RegisterCommands(bot);
    }
    std::cout << "Logged in as " << bot.me.username << "#" << bot.me.discriminator << " (" << bot.me.id << ")\n";
  });*/

  bot.start(dpp::st_wait);
  return bot;
}
void CBot::create(std::string token) {
  bot = new dpp::cluster(token);
}
}
