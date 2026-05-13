cmake_minimum_required(VERSION 3.15)
project(sshman)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(sshman
  src/sshman.cpp
  src/auth.cpp
  src/cmd.cpp
  src/config.cpp
  src/helpers.cpp
)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SODIUM REQUIRED libsodium)

target_include_directories(sshman PRIVATE ${SODIUM_INCLUDE_DIRS})
target_link_libraries(sshman PRIVATE ${SODIUM_LIBRARIES})

install(TARGETS sshman DESTINATION bin)
