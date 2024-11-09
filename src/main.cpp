// Copyright (c) 2024 Alexandru Constantin

#include <ansi_lib/ansi_lib.h>
#include <types/config.h>
#include <iostream>
#include <string>

void print_help(std::optional<std::string> error = std::nullopt);

#define PRINT_VAL(val) std::cout << #val << " = " << val << '\n';

int main(int argc, char* argv[]) {
  ANSI_LIB_WINDOWS_INIT();

  auto [result, error] = ac_scanner::parse_args(argc, argv);

  if (error) {
    print_help(error);
    return 1;
  }

  if (result.help) {
    print_help();
    return 0;
  }

  if (result.version) {}

  // STEPS:
  //  1. GET ADDRESS
  //  2. SCAN THROUGH EVERY PORT
  //  3. IF CONNECTION IS FOUND, SAVE PORT

  return 0;
}

void print_help(std::optional<std::string> error) {
  if (error) {
    std::cout << error.value() << "\n";
  }
  std::cout << "usage: ac_scanner [-v | --version] [-h | --help] \n";
  std::cout << "                  [-s | --system] [-u | --user] [-d | "
            << "--dynamic] [-a | "
            << "--all]\n"
            << "                  <ip_address> \n";
}
