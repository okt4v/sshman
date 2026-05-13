#include "auth.h"
#include "config.h"
#include "helpers.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sodium.h>
#include <sodium/crypto_pwhash.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

std::string read_passwd(const std::string &prompt) {
  std::cout << prompt;
  struct termios t;
  tcgetattr(STDIN_FILENO, &t);
  t.c_lflag &= ~ECHO;
  tcsetattr(STDIN_FILENO, TCSANOW, &t);

  std::string passwd;
  std::getline(std::cin, passwd);

  t.c_lflag |= ECHO;
  tcsetattr(STDIN_FILENO, TCSANOW, &t);
  std::cout << "\n";

  return passwd;
}

void create_session(int session_timeout) {
  std::ofstream file(session_path());
  if (!file.is_open())
    return;
  file << std::time(nullptr) + parse_config().session_timeout;
  std::filesystem::permissions(session_path(),
                               std::filesystem::perms::owner_read |
                                   std::filesystem::perms::owner_write,
                               std::filesystem::perm_options::replace);
}

bool session_valid() {
  std::ifstream file(session_path());
  if (!file.is_open())
    return false;
  long expiry;
  file >> expiry;
  return std::time(nullptr) < expiry;
}

bool login() {
  if (!std::filesystem::exists(sshman_path() / "auth"))
    create_auth();

  if (session_valid())
    return true;

  std::filesystem::path passwd_file = sshman_path() / "auth" / "passwd";
  std::string stored_hash;
  std::ifstream file(passwd_file);
  std::getline(file, stored_hash);

  for (int i = 0; i < 3; ++i) {
    std::string entered_string = read_passwd("Please enter your password: ");
    if (crypto_pwhash_str_verify(stored_hash.c_str(), entered_string.c_str(),
                                 entered_string.size()) != 0) {
      std::cout << "Incorrect password, please try again." << std::endl;
    } else {
      create_session(parse_config().session_timeout);
      return true;
    }
  }
  return false;
}
