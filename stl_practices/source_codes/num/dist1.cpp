// num/dist1.cpp

#include <iomanip>
#include <iostream>
#include <map>
#include <random>
#include <string>

template <typename Distr, typename Eng>
void distr(Distr d, Eng e, const std::string& name) {
  // print min, max and four example values
  std::cout << name << ":" << std::endl;
  std::cout << "- min(): " << d.min() << std::endl;
  std::cout << "- max(): " << d.max() << std::endl;
  std::cout << "- values: " << d(e) << ' ' << d(e) << ' ' << d(e) << ' ' << d(e) << std::endl;

  // count the generated values (converted to integral values)
  std::map<long long, int> valuecounter;
  for (size_t i = 0; i < 200000; i++) {
    valuecounter[d(e)]++;
  }

  // and print the resulting distribution
  std::cout << "====" << std::endl;
  for (auto elem : valuecounter) {
    std::cout << std::setw(3) << elem.first << ": " << elem.second << std::endl;
  }
  std::cout << "====" << std::endl;
  std::cout << std::endl;
}

int main() {
  std::knuth_b e;

  std::uniform_real_distribution<> ud(0, 10);
  distr(ud, e, "uniform_real_distribution");

  std::normal_distribution<> nd;
  distr(nd, e, "normal_distribution");

  std::exponential_distribution<> ed;
  distr(ed, e, "exponential_distribution");

  std::gamma_distribution<> gd;
  distr(gd, e, "gamma_distribution");
}