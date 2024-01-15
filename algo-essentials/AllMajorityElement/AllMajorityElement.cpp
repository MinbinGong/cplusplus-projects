// AllMajorityElement.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

vector<int> majorityElement(const vector<int>& nums) {
  int count1 = 0, count2 = 0;
  int candidate1 = 0, candidate2 = 1;

  for (auto const num : nums) {
    if (candidate1 == num) {
      ++count1;
    } else if (candidate2 == num) {
      ++count2;
    } else if (count1 == 0) {
      candidate1 = num;
      count1 = 1;
    } else if (count2 == 0) {
      candidate2 = num;
      count2 = 1;
    } else {
      --count1;
      --count2;
    }
  }

  vector<int> result;
  for (auto c : vector<int>{candidate1, candidate2}) {
    if (std::count(nums.begin(), nums.end(), c) > nums.size() / 3) {
      result.push_back(c);
    }
  }
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
