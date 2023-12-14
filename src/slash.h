#include <dpp/dpp.h>

namespace Bot {
namespace PingCommand {
void registerCommand(dpp::cluster& bot);
void execute(const dpp::slashcommand_t& event);
}
namespace HelloCommand {
void registerCommand(dpp::cluster& bot);
void execute(const dpp::slashcommand_t& event);
}
namespace AvatarCommand {
void registerCommand(dpp::cluster& bot);
void execute(const dpp::slashcommand_t& event);
std::string getAvatarURL(dpp::user& user, dpp::image_type format);
}
void RegisterCommands(dpp::cluster& bot);
}
struct Command {
  std::function<void(dpp::cluster& bot)> registerFunc;
  std::function<void(const dpp::slashcommand_t& event)> eventFireFunc;
};

const std::unordered_map<std::string, Command> Commands = {
  {"ping", (struct Command){.registerFunc = &Bot::PingCommand::registerCommand, .eventFireFunc = &Bot::PingCommand::execute,}},
  {"hello", (struct Command){.registerFunc = &Bot::HelloCommand::registerCommand, .eventFireFunc = &Bot::HelloCommand::execute,}},
  {"avatar", (struct Command){.registerFunc = &Bot::AvatarCommand::registerCommand, .eventFireFunc = &Bot::AvatarCommand::execute,}},
};
