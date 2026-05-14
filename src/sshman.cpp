#include "auth.h"
#include "cmd.h"

#include <sodium.h>
#include <stdexcept>

int main(int argc, char *argv[]) {
  if (sodium_init() < 0)
    throw std::runtime_error("Failed to initialize libsodium");

  if (!login())
    return 0;

  for (int i = 1; i < argc; ++i) {
    std::string a = argv[i];
    if (a == "-l" || a == "--list") {
    } else if (a == "-c" || a == "--connect") {
      if (i + 1 >= argc)
        throw std::runtime_error("Expected a name after -c");
      std::string name = argv[i + 1];
      cmd_connect(name);
      ++i;
    } else if (a == "-n" || a == "--new") {
      cmd_new();
    }
  }

  return 0;
}
