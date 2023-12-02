#include <dpp/dpp.h>

namespace Bot {
dpp::cluster& startBot(std::string token);
//extern dpp::cluster* bot;
class CBot {
public:
  static dpp::cluster* bot;
  static void create(std::string token);
};
}
