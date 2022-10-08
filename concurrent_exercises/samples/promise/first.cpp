#include <functional>
#include <future>
#include <iostream>
#include <thread>

void print_int(std::future<int> &fut) {
  int x = fut.get();
  std::cout << "Value: " << x << '\n';
}

int main(int argc, const char *argv[]) {
  std::promise<int> prom;
  std::future<int> fut = prom.get_future();
  std::thread t(print_int, std::ref(fut));
  prom.set_value(10);
  t.join();

  std::cout << "All threads joined" << std::endl;

  return 0;
}