#include "../event.h"
#include "../slash.h"
#include "../logger.h"

namespace Bot {
namespace ReadyEvent {
void Register(dpp::cluster& bot) {
  bot.on_ready([&bot](const dpp::ready_t& event) {
    if (dpp::run_once<struct register_bot_commands>()) {
      Bot::RegisterCommands(bot);
    }
    Logger::log(std::format("Logged in as {}#{} ({})\n", bot.me.username, bot.me.discriminator, bot.me.id.str()));
  });
}
}
}
