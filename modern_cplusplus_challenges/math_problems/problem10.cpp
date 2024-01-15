#include <bitset>
#include <iostream>
#include <string>

unsigned int gray_encode(unsigned int const num) { return num ^ (num >> 1); }

unsigned int gray_decode(unsigned int gray) {
  for (unsigned int bit = 1U << 31; bit > 1; bit >>= 1) {
    if (gray & bit) {
      gray ^= bit >> 1;
    }
  }
  return gray;
}

std::string to_binary(unsigned int value, int const digits) {
  return std::bitset<32>(value).to_string().substring(32 - digits, digits);
}