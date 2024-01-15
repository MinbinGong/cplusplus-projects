#include <chrono>
#include <iostream>
#include <mutex>
#include <random>
#include <string>
#include <string_view>
#include <thread>
#include <vector>

class logger {
 private:
  std::mutex mt;

 protected:
  logger(){};

 public:
  static logger &instance() {
    static logger lg;
    return lg;
  }

  logger(logger const &) = delete;
  logger &operator=(logger const &) = delete;

  void log(std::string_view message) {
    std::lock_guard<std::mutex> lock(mt);
    std::cout << "LOG:" << message << std::endl;
  }
};

int main() {
  std::vector<std::thread> modules;

  for (int id = 0; id < 6; id++) {
    modules.emplace_back([id]() {
      std::random_device rd;
      std::mt19937 mt(rd());
      std::uniform_int_distribution<> ud(100, 1000);

      logger::instance().log("module: " + std::to_string(id) + " started");
      std::this_thread::sleep_for(std::chrono::milliseconds(ud(mt)));

      logger::instance().log("module " + std::to_string(id) + " finished");
    });
  }

  for (auto &m : modules) {
    m.join();
  }

  return 0;
}
