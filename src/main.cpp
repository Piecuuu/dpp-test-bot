#include <dpp/dpp.h>
#include "config.h"
#include "slash.h"

const std::unordered_map<std::string, std::function<void(const dpp::slashcommand_t& event)>> Commands = {
  {"ping", &Bot::PingCommand::execute},
  {"hello", &Bot::HelloCommand::execute},
};

int main() {
  YAML::Node config = Config::loadConfig();
  std::string token = config["token"].as<std::string>();

  dpp::cluster bot(token);

  //bot.on_log(dpp::utility::cout_logger());

  bot.on_slashcommand([](const dpp::slashcommand_t& event) {
    std::string cmd = event.command.get_command_name();
    auto it = Commands.find(cmd);
    //assert(it == Commands.end());
    it->second(event);
  });

  bot.on_ready([&bot](const dpp::ready_t& event) {
    if (dpp::run_once<struct register_bot_commands>()) {
      Bot::RegisterCommands(bot);
    }
    std::cout << "Logged in as " << bot.me.username << "#" << bot.me.discriminator << " (" << bot.me.id << ")\n";
  });

  bot.start(dpp::st_wait);
}
