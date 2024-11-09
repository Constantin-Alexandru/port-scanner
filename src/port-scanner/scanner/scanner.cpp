// Copyright (c) 2024 Alexandru Constantin

#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <scanner/scanner.h>
#include <sys/socket.h>
#include <types/config.h>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

namespace ac_scanner {

std::mutex mutex;

bool check_socket(char ip_address[], uint16_t port) {
  int sockfd;
  struct sockaddr_in connection;

  if (inet_pton(AF_INET, ip_address, &connection.sin_addr) < 1) {
    std::cerr << "Problem loading IP address " << ip_address << '\n';
    return false;
  }

  std::memset(&connection, 0, sizeof(connection));
  connection.sin_family = AF_INET;
  connection.sin_addr.s_addr = inet_addr(ip_address);
  connection.sin_port = htons(port);

  if (connection.sin_addr.s_addr == (in_addr_t)(-1)) {
    std::cerr << "Failed to convert ip_address " << ip_address << '\n';
    return false;
  }

  sockfd = socket(AF_INET, SOCK_STREAM, 0);

  if (sockfd < 0) {
    std::cerr << "Unable to connect to socket: " << strerror(errno) << '\n';
    close(sockfd);
    return false;
  }

  int flags = fcntl(sockfd, F_GETFL, 0);
  if (flags < 0) {
    std::cerr << "Failed to get socket flags\n";
    close(sockfd);
    return false;
  }

  if (fcntl(sockfd, F_SETFL, flags | O_NONBLOCK) < 0) {
    std::cerr << "Failed to set non-blocking mode\n";
    close(sockfd);
    return false;
  }

  if (connect(sockfd, (struct sockaddr*)&connection, sizeof(connection)) == 0) {
    close(sockfd);
    return true;
  }

  close(sockfd);

  return false;
}

void scan_range(const uint16_t start_port, const uint16_t end_port,
                char ip_address[], std::vector<uint16_t>& open_ports) {
  for (uint16_t port = start_port; port < end_port; port++) {
    std::lock_guard<std::mutex> lock(mutex);
    if (check_socket(ip_address, port))
      open_ports.push_back(port);
  }
}

std::vector<uint16_t> launch_scanner(Config config) {
  using std::thread;

  int thread_count = thread::hardware_concurrency();

  std::vector<thread> threads(thread_count);

  auto [start_port, end_port] = ac_scanner::get_port_range(config);

  uint16_t ports_per_thread = (end_port - start_port + 1) / thread_count;

  std::vector<uint16_t> open_ports;

  for (int thread_ind = 0; thread_ind < thread_count; thread_ind++) {
    uint16_t thread_start_port = thread_ind * ports_per_thread;
    uint16_t thread_end_port = thread_ind * ports_per_thread + ports_per_thread;

    threads[thread_ind] = thread(scan_range, thread_start_port, thread_end_port,
                                 config.ip_address, std::ref(open_ports));
  }

  for (thread& thread : threads) {
    thread.join();
  }

  return open_ports;
}

}  // namespace ac_scanner
