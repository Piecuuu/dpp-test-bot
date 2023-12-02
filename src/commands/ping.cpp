#include "../slash.h"

namespace Bot {
namespace PingCommand {
void registerCommand(dpp::cluster& bot) {
  bot.global_command_create(dpp::slashcommand("ping", "Ping pong!", bot.me.id));
}
void execute(const dpp::slashcommand_t& event) {
  event.reply("Pong!");
}
}
}
