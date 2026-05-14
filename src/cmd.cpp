#include "cmd.h"
#include "auth.h"
#include "helpers.h"

#include <filesystem>
#include <fstream>

void cmd_list() {}

void cmd_connect(std::string name) {}

void cmd_new() {
  if (!std::filesystem::exists(sshman_path() / "connections.csv"))
    create_storage();

  std::string entered_name;
  std::string entered_ip;
  std::string entered_port;
  std::string entered_user;
  std::string entered_passwd;

  std::cout << "Name: ";
  std::cin >> entered_name;
  std::cout << "IP: ";
  std::cin >> entered_ip;
  std::cout << "Port: ";
  std::cin >> entered_port;
  std::cout << "User: ";
  std::cin >> entered_user;
  entered_passwd = read_passwd("Password: ");

  std::ofstream file(sshman_path() / "connections.csv", std::ios::app);

  file << entered_name << "," << entered_ip << "," << entered_port << ","
       << entered_user << "," << entered_passwd << "\n";
}
