// AddBinary.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

std::string addBinary(std::string& a, std::string& b) {
  std::string res{};
  unsigned int i = a.length() - 1, j = b.length() - 1, carry = 0;

  while (i >= 0 || j >= 0 || carry > 0) {
    int x = i < 0 ? 0 : a[i--] - '0';
    int y = j < 0 ? 0 : b[j--] - '0';
    int sum = x + y + carry;
    res.insert(res.begin(), (sum % 2) + '0');
    carry = sum / 2;
  }
  return res;
}

int main() { std::cout << "Hello World!\n"; }

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files
//   to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
