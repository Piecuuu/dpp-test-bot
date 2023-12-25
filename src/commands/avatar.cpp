#include "../slash.h"
#include "../config.h"
#include "../bot.h"
#include <format>
#include <opencv2/opencv.hpp>
#include <curl/curl.h>
#include "../logger.h"

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
  std::string url = Bot::AvatarCommand::getAvatarURL(user, dpp::i_webp);
  dpp::embed embed = dpp::embed()
    .set_color(get_prominent_color(convert_data_to_mat(download_image(url))))
    .set_image(url)
    .set_description(std::format("[`[png]`]({}) [`[jpg]`]({}) [`[webp]`]({})",
      getAvatarURL(user, dpp::i_png), getAvatarURL(user, dpp::i_jpg),
      getAvatarURL(user, dpp::i_webp)
    ))
    .set_author(dpp::embed_author{
      .name = user.format_username() + "'s avatar",
      .icon_url = url,
    });

  dpp::message message = dpp::message(event.command.channel_id, embed);
  event.edit_original_response(message);
}
std::string getAvatarURL(dpp::user& user, dpp::image_type format) {
  return user.get_avatar_url(512U, format, true);
}
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* data) {
    size_t total_size = size * nmemb;
    data->append((char*)contents, total_size);
    return total_size;
}
uint32_t rgb_to_color(uint8_t r, uint8_t g, uint8_t b) {
  return (r << 16) + (g << 8) + b;
}
uint32_t get_prominent_color(cv::Mat image) {
  std::vector<cv::Vec3f> pixels;
  for (int y = 0; y < image.rows; y++) {
    for (int x = 0; x < image.cols; x++) {
      cv::Vec3b pixel = image.at<cv::Vec3b>(y, x);
      pixels.push_back(cv::Vec3f(pixel[0], pixel[1], pixel[2]));
    }
  }

  int k = 1; // 1 color
  cv::TermCriteria criteria(cv::TermCriteria::EPS + cv::TermCriteria::COUNT, 10, 1.0);
  int attempts = 5;
  cv::Mat labels, centers;
  kmeans(pixels, k, labels, criteria, attempts, cv::KMEANS_RANDOM_CENTERS, centers);

  cv::Vec3f prominentColor = centers.at<cv::Vec3f>(0);
  int32_t rgb = rgb_to_color((uint8_t)prominentColor[2], (uint8_t)prominentColor[1], (uint8_t)prominentColor[0]);

  return rgb;
}
std::string download_image(std::string& url) {
  CURL* curl;
  CURLcode res;
  std::string data;

  curl_global_init(CURL_GLOBAL_DEFAULT);
  curl = curl_easy_init();

  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);

    res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
      Logger::error(std::format("curl_easy_perform() failed: %s\n", curl_easy_strerror(res)));
    }

    curl_easy_cleanup(curl);
  }

  curl_global_cleanup();

  return data;
}
cv::Mat convert_data_to_mat(const std::string& data) {
  std::vector<uchar> img_data(data.begin(), data.end());
  cv::Mat image = cv::imdecode(img_data, cv::IMREAD_COLOR);
  return image;
}
}
}
