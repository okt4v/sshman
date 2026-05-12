#pragma once

#include <filesystem>
#include <iostream>

std::filesystem::path home_path();
std::filesystem::path sshman_path();
std::filesystem::path config_path();
std::filesystem::path connections_path();

void create_config();
