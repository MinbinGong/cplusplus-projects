// LongestConsecutive.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;

int longestConsecutive(const vector<int>& nums) {
  unordered_set<int> my_set;
  for (auto i : nums) {
    my_set.insert(i);
  }

  int longest = 0;
  for (auto i : nums) {
    int length = 1;
    for (int j = i - 1; my_set.find(j) != my_set.end(); j++) {
      my_set.erase(j);
      ++length;
    }

    for (int j = i + 1; my_set.find(j) != my_set.end(); j++) {
      my_set.erase(j);
      ++length;
    }

    longest = max(longest, length);
  }

  return longest;
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
