#include "../event.h"
#include "../slash.h"

namespace Bot {
namespace ReadyEvent {
void Register(dpp::cluster& bot) {
  bot.on_ready([&bot](const dpp::ready_t& event) {
    if (dpp::run_once<struct register_bot_commands>()) {
      Bot::RegisterCommands(bot);
    }
    std::cout << "Logged in as " << bot.me.username << "#" << bot.me.discriminator << " (" << bot.me.id << ")\n";
  });
}
}
}
