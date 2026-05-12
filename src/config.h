#pragma once

#include <filesystem>
#include <iostream>
#include <string.h>

struct Config {
  int session_timeout;
  bool check_online;
};

Config parse_config();
