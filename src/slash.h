#include <dpp/dpp.h>
#include <opencv2/opencv.hpp>

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
cv::Mat convert_data_to_mat(const std::string& data);
std::string download_image(std::string& url);
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* data);
uint32_t get_prominent_color(cv::Mat image);
uint32_t rgb_to_color(uint8_t r, uint8_t g, uint8_t b);
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
