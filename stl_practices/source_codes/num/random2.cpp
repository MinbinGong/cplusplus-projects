// num/random2.cpp

#include <iostream>
#include <random>
#include <sstream>

void printNumbers(std::default_random_engine& dre) {
  for (size_t i = 0; i < 6; i++) {
    std::cout << dre() << " ";
  }
  std::cout << std::endl;
}

int main() {
  // create engine and generate numbers
  std::default_random_engine dre;
  printNumbers(dre);

  // create equal engine and generate numbers
  std::default_random_engine dre2;
  printNumbers(dre2);

  // create engine with initial state specified by a seed
  std::default_random_engine dre3(42);
  printNumbers(dre3);

  // save state of engine dre
  std::stringstream engineState;
  engineState << dre;

  // generate numbers according to current state of dre
  printNumbers(dre);

  // restore saved state of engine dre and create numbers again
  engineState >> dre;
  printNumbers(dre);

  // restore saved state of engine dre, skip 2 numbers and create numbers again
  engineState.clear();
  engineState.seekg(0);
  engineState >> dre;
  dre.discard(2);
  printNumbers(dre);
}