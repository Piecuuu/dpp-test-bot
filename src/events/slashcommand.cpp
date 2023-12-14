#include "../event.h"
#include "../slash.h"

namespace Bot {
namespace SlashCommandEvent {
void Register(dpp::cluster& bot) {
  bot.on_slashcommand([](const dpp::slashcommand_t& event) {
    std::string cmd = event.command.get_command_name();
    auto it = Commands.find(cmd);
    it->second.eventFireFunc(event);
  });
}
}
}
