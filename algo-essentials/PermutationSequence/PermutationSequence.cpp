// PermutationSequence.cpp : This file contains the 'main' function. Program execution begins and ends there.
// ¿µÍÐ±àÂë

#include <iostream>
#include <iterator>
#include <string>
using namespace std;

int factorial(int n) {
  int result = 1;
  for (int i = 1; i < n + 1; i++) {
    result *= i;
  }
  return result;
}

string kth_permutation(string& s, int k) {
  const int n = s.size();
  string res{};

  int base = factorial(n - 1);
  --k;

  for (int i = n - 1; i > 0; i--, k %= base, base /= i) {
    auto a = next(s.begin(), k / base);
    res.push_back(*a);
    s.erase(a);
  }

  res.push_back(s[0]);
  return res;
}

string getPermutation(int n, int k) {
  string s(n, '0');
  string result;
  for (int i = 0; i < n; i++) {
    s[i] += i + 1;
  }

  return kth_permutation(s, k);
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
