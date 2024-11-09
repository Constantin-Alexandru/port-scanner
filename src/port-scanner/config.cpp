// Copyright (c) 2024 Alexandru Constantin

#include <types/config.h>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

namespace ac_scanner {

Result<Config> parse_args(int argc, char* argv[]) {
  if (argc < 2) {
    return Result<Config>(Config(), "Not enough arguments.");
  }

  if (argc > 10) {
    return Result<Config>(Config(), "Too many arguments.");
  }

  const std::vector<std::string_view> args(argv + 1, argv + argc);

  Config config;

  for (size_t i = 0; i < args.size(); ++i) {
    const std::string_view& arg = args[i];

    std::cout << "[" << i << "] " << arg << '\n';

    if (arg == "-v" || arg == "--version") {
      config.version = 1;
      continue;
    }

    if (arg == "-h" || arg == "--help") {
      config.help = 1;
      continue;
    }

    if (arg == "-s" || arg == "--system") {
      config.system_ports = 1;
      continue;
    }

    if (arg == "-u" || arg == "--user") {
      config.user_ports = 1;
      continue;
    }

    if (arg == "-d" || arg == "--dynamic") {
      config.dynamic_ports = 1;
      continue;
    }

    if (arg == "-a" || arg == "--all") {
      config.system_ports = 1;
      config.user_ports = 1;
      config.dynamic_ports = 1;
      continue;
    }

    std::strncpy(config.ip_address, std::string(arg).c_str(),
                 std::min(std::string(arg).size(), size_t(50)));
  }

  if (config.ip_address[0] == '\0') {
    std::strncpy(config.ip_address, "localhost", 10);
  }

  return Result<Config>(config);
}
}  // namespace ac_scanner
