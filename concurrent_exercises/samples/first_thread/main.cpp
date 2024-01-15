#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <thread>
#include <vector>

int main(int argc, const char *argv[]) {
  std::vector<std::thread> threads;

  for (size_t i = 0; i < 5; i++) {
    threads.push_back(
      std::thread([]() { std::cout << "Hello from thread " << std::this_thread::get_id() << std::endl; }));
  }

  for (auto &thread : threads) {
    thread.join();
  }

  std::cout << "Hello from main()" << std::endl;

  return EXIT_SUCCESS;
}