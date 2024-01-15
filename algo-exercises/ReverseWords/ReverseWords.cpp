// ReverseWords.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <algorithm>
#include <iostream>
#include <string>

std::string reverseWords(const std::string& s) {
  std::string tmpStr{s};
  std::reverse(tmpStr.begin(), tmpStr.end());

  size_t index{0};
  std::string ret{};
  while (index < tmpStr.length()) {
    size_t bIndex{index}, eIndex{index};
    eIndex = tmpStr.find(' ');
    std::string s = tmpStr.substr(bIndex, eIndex - bIndex);
    std::reverse(s.begin(), s.end());
    ret += s + " ";
    index = eIndex + 1;
  }

  return ret.substr(0, ret.length() - 2);
}

int main() {
  std::string s{"the sky is blue"};
  std::cout << s << std::endl;

  // reverse(s.begin(), s.end());
  // std::cout << "reversed: " << s << std::endl;

  std::string reversedStr = reverseWords(s);
  std::cout << reversedStr << std::endl;

  return 0;
}
