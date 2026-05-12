#include "helpers.h"

#include <cstdlib>
#include <filesystem>
#include <stdexcept>

std::filesystem::path home_path() {
  const char *home_path = std::getenv("HOME");
  if (home_path == nullptr) {
    throw std::runtime_error("HOME env var not set");
  }

  return home_path;
}

std::filesystem::path sshman_path(std::filesystem::path home_path) {
  return home_path / ".config" / "sshman";
}

std::filesystem::path config_path(std::filesystem::path sshman_path) {
  return sshman_path / "config";
}

std::filesystem::path connections_path(std::filesystem::path sshman_path) {
  return sshman_path / "connections.csv";
}
