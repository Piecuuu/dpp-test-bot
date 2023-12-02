#include <yaml-cpp/yaml.h>
namespace Config {

YAML::Node loadConfig();
void createConfig();

extern YAML::Node* config;

}
