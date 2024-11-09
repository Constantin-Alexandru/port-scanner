// Copyright (c) 2024 Alexandru Constantin

#include <ansi_lib/ansi_lib.h>
#include <scanner/scanner.h>
#include <types/config.h>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

// TODO: Generalise the scanner so it works with more than just linux

void print_version();
void print_help(std::optional<std::string> error = std::nullopt);

int main(int argc, char* argv[]) {
  ANSI_LIB_WINDOWS_INIT();

  auto [config, error] = ac_scanner::parse_args(argc, argv);

  if (error) {
    print_help(error);
    return 1;
  }

  if (config.help) {
    print_help();
    return 0;
  }

  if (config.version) {
    print_version();
  }

  std::cout << "Scanning " << config.ip_address << " ...\n";

  std::vector<uint16_t> ports = ac_scanner::launch_scanner(config);

  std::cout << "Scanned " << config.ip_address << " and found " << ports.size()
            << " open ports:\n";

  for (uint16_t& port : ports) {
    std::cout << "\t- " << port << '\n';
  }

  return 0;
}

void print_version() {
  std::cout << "ac_scanner version " << AC_SCANNER_MAJOR << "."
            << AC_SCANNER_MINOR << "." << AC_SCANNER_PATCH << '\n';
}

void print_help(std::optional<std::string> error) {
  if (error) {
    std::cout << error.value() << "\n";
  }
  print_version();
  std::cout << "usage: ac_scanner [-v | --version] [-h | --help] \n";
  std::cout << "                  [-s | --system] [-u | --user] [-d | "
            << "--dynamic] [-a | "
            << "--all]\n"
            << "                  <ip_address> \n";
}
