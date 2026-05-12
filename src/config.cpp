#include "config.h"
#include <fstream>

void create_config() {}

Config parse_config(std::filesystem::path home) {
  std::ifstream file(home / ".config" / "sshman" / "config");
  if (!file.is_open()) {
    std::cout << "Failed to find config, generating default..." << std::endl;
  }
}
