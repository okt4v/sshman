#include <cstddef>
#include <fstream>
#include <map>

#include "config.h"
#include "helpers.h"

Config parse_config() {
  std::ifstream file(config_path());
  if (!file.is_open()) {
    std::cout << "Failed to find config, generating default config..."
              << std::endl;
    create_config();
  }

  std::map<std::string, std::string> config_map;
  std::string line;

  while (std::getline(file, line)) {
    if (line.empty() || line[0] == '#')
      continue;
    std::size_t eq = line.find('=');
    if (eq == std::string::npos)
      continue;
    std::string key = line.substr(0, eq);
    std::string value = line.substr(eq + 1);
    config_map[key] = value;
  }

  Config config;
  config.session_timeout = std::stoi(config_map["session_timeout"]);
  config.check_online = config_map["check_online"] == "true";

  return config;
}
