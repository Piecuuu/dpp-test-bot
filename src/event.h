#include <dpp/dpp.h>

namespace Bot {
namespace ReadyEvent {
void Register(dpp::cluster& bot);
}
namespace SlashCommandEvent {
void Register(dpp::cluster& bot);
}
void RegisterEvents(dpp::cluster& bot);
}

const std::unordered_map<std::string, std::function<void(dpp::cluster& bot)>> Events = {
  {"Ready", &Bot::ReadyEvent::Register},
  {"SlashCommand", &Bot::SlashCommandEvent::Register},
};
