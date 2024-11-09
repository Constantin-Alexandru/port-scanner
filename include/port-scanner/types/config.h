// Copyright (c) 2024 Alexandru Constantin

#ifndef INCLUDE_PORT_SCANNER_TYPES_CONFIG_H_
#define INCLUDE_PORT_SCANNER_TYPES_CONFIG_H_

#include <types/Result.h>
#include <cstdint>
#include <utility>

namespace ac_scanner {

//=== AC SCANNER VERSION ===

#define AC_SCANNER_MAJOR 0
#define AC_SCANNER_MINOR 2
#define AC_SCANNER_PATCH 0

//=== DEFAULT PORT RANGE ===

const uint16_t MIN_PORT = 0;
const uint16_t MAX_PORT = 65535;

//=== RANGE PORT VARIABLES ===

const uint16_t MIN_SYSTEM_PORT = 0;
const uint16_t MAX_SYSTEM_PORT = 1023;
const uint16_t MIN_USER_PORT = 1024;
const uint16_t MAX_USER_PORT = 49151;

const uint16_t MIN_DYNAMIC_PORT = 49152;
const uint16_t MAX_DYNAMIC_PORT = 65535;

enum class PORT_RANGES {
  SYSTEM = 1 << 0,
  USER = 1 << 1,
  DYNAMIC = 1 << 2,
  ALL = 1 & 1 << 1 & 1 << 2
};

struct Config {
  unsigned help : 1 = 0;
  unsigned version : 1 = 0;
  unsigned system_ports : 1 = 0;
  unsigned user_ports : 1 = 0;
  unsigned dynamic_ports : 1 = 0;

  char ip_address[50] = "";
} __attribute__((packed));  // Config

Result<Config> parse_args(int argc, char* argv[]);

std::pair<uint16_t, uint16_t> get_port_range(Config config);

}  // namespace ac_scanner

#endif  // INCLUDE_PORT_SCANNER_TYPES_CONFIG_H_
