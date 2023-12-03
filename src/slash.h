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

const std::unordered_map<std::string, std::function<void(const dpp::slashcommand_t& event)>> Commands = {
  {"ping", &Bot::PingCommand::execute},
  {"hello", &Bot::HelloCommand::execute},
  {"avatar", &Bot::AvatarCommand::execute},
};
