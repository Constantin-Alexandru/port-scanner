// Copyright (c) 2024 Alexandru Constantin

#include <types/config.h>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <string>
#include <utility>
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
    std::strncpy(config.ip_address, "127.0.0.1", std::strlen("127.0.0.1") + 1);
  }

  return Result<Config>(config);
}

std::pair<uint16_t, uint16_t> get_port_range(Config config) {
  uint16_t start_port = 0;
  uint16_t end_port = 0;

  if (config.dynamic_ports) {
    start_port = MIN_DYNAMIC_PORT;
    end_port = MAX_DYNAMIC_PORT;
  }

  if (config.user_ports) {
    start_port = MIN_USER_PORT;
    if (!end_port)
      end_port = MAX_USER_PORT;
  }

  if (config.system_ports) {
    start_port = MIN_SYSTEM_PORT;
    if (!end_port)
      end_port = MAX_SYSTEM_PORT;
  }

  return std::make_pair(start_port, end_port);
}
}  // namespace ac_scanner
