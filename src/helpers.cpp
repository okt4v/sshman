#include "helpers.h"

#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <stdexcept>

std::filesystem::path home_path() {
  const char *home_path = std::getenv("HOME");
  if (home_path == nullptr) {
    throw std::runtime_error("HOME env var not set");
  }

  return home_path;
}

std::filesystem::path sshman_path() {
  return home_path() / ".config" / "sshman";
}

std::filesystem::path config_path() { return sshman_path() / "config"; }

std::filesystem::path connections_path() {
  return sshman_path() / "connections.csv";
}

void create_config() {
  std::filesystem::create_directory(sshman_path());
  std::ofstream file(config_path());
  file << "##################\n";
  file << "# DEFAULT CONFIG #\n";
  file << "##################\n\n";
  file << "session_timeout=900\n";
  file << "check_online=false\n";
}
