#pragma once

#include <iostream>
#include <string.h>

std::string read_passwd(const std::string &prompt);
bool login();
bool session_valid();
void create_session(int session_timeout);
