#include "../slash.h"

namespace Bot {
namespace HelloCommand {
void registerCommand(dpp::cluster& bot) {
  bot.global_command_create(dpp::slashcommand("hello", "Hello!", bot.me.id));
}
void execute(const dpp::slashcommand_t& event) {
  event.reply("Hi");
}
}
}
