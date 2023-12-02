#include "../slash.h"
#include "../config.h"
#include "../bot.h"

namespace Bot {
namespace AvatarCommand {
void registerCommand(dpp::cluster& bot) {
  bot.global_command_create(dpp::slashcommand("avatar", "Displays the avatar of a specified user.", bot.me.id)
    .add_option(
      dpp::command_option(dpp::co_user, "user", "The user to display the avatar of", false)
    ));
}
void execute(const dpp::slashcommand_t& event) {
  event.thinking();
  auto param = event.get_parameter("user");
  dpp::user user;
  user = param.index() == 0 ? event.command.usr : Bot::CBot::bot->user_get_cached_sync(std::get<dpp::snowflake>(param)); // Terrible code, might clean up later
  std::string url = Bot::AvatarCommand::getAvatarURL(&user);
  dpp::embed embed = dpp::embed()
    .set_color(Config::config["colors"]["neutral-blue"].as<uint32_t>()) // TODO: Set it to the prominent color of the avatar
    .set_image(url)
    .set_author(dpp::embed_author{
      .name = "Avatar of " + user.format_username(),
      .icon_url = url,
    });

  dpp::message message = dpp::message(event.command.channel_id, embed);
  event.edit_original_response(message);
}
std::string getAvatarURL(dpp::user* user) {
  return user->get_avatar_url(512U, dpp::i_webp, true);
}
}
}
