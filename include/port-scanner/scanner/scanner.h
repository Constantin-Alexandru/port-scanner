// Copyright (c) 2024 Alexandru Constantin

#ifndef INCLUDE_PORT_SCANNER_SCANNER_SCANNER_H_
#define INCLUDE_PORT_SCANNER_SCANNER_SCANNER_H_

#include <types/config.h>
#include <vector>

namespace ac_scanner {
std::vector<uint16_t> launch_scanner(Config config);
}

#endif  // INCLUDE_PORT_SCANNER_SCANNER_SCANNER_H_
