#include <algorithm>
#include <cstddef>
#include <string>
#include <vector>

enum class procstatus { suspended, running };

enum class platforms { p32bit, p64bit };

struct procinfo {
  int id;
  std::string name;
  procstatus status;
  std::string account;
  size_t memory;
  platforms platform;
};

std::string status_to_string(procstatus const status) {
  if (status == procstatus::suspended) {
    return "suspended";
  } else {
    return "running";
  }
}

std::string platform_to_string(platforms const platform) {
  if (platform == platforms::p32bit) {
    return "32-bit";
  } else {
    return "64-bit";
  }
}

void print_processes(std::vector<procinfo> processes) {
  std::sort(std::begin(processes), std::end(processes),
            [](procinfo const &p1, procinfo const &p2) { return p1.name < p2.name; });

  for (auto const &pi : processes) {
    std::cout << std::left << std::setw(25) << std::setfill(' ') << pi.name;
    std::cout << std::left << std::setw(8) << std::setfill(' ') << pi.id;
    std::cout << std::left << std::setw(12) << std::setfill(' ') << status_to_string(pi.status);
    std::cout << std::left << std::setw(15) << std::setfill(' ') << pi.account;
    std::cout << std::right << std::setw(10) << std::setfill(' ') << int(pi.memory / 1024);
    std::cout << std::left << ' ' << platform_to_string(pi.platform);
    std::cout << std::endl;
  }
}