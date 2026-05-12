#pragma once

#include <filesystem>
#include <iostream>
#include <string.h>

struct Config {
  int session_timeout;
  std::string csv_path;
  bool check_online;
};

std::filesystem::path config_path();
void create_config();
Config parse_config(std::filesystem::path home);
