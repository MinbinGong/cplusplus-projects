/*
 * @lc app=leetcode.cn id=583 lang=cpp
 * Beautiful Array
 * An array nums of length n is beautiful if:
 *
 * nums is a permutation of the integers in the range [1, n]
 * For every 0 <= i < j < n, there is no index k with i < k < j where 2 * nums[k] == nums[i] + nums[j].
 * Given the integer n, return any beautiful array nums of length n. There will be at least one valid answer for the
 * given n.
 */
#include <vector>
using namespace std;

class Solution {
 public:
  vector<int> beautifulArray1(int n) {
    vector<int> ans;
    if (n == 1) {
      ans.push_back(1);
      return ans;
    }
    vector<int> left = beautifulArray((n + 1) / 2);
    vector<int> right = beautifulArray(n / 2);
    for (int i = 0; i < left.size(); i++) {
      ans.push_back(left[i] * 2 - 1);
    }
    for (int i = 0; i < right.size(); i++) {
      ans.push_back(right[i] * 2);
    }
    return ans;
  }

  vector<int> beautifulArray2(int n) {
    vector<int> ans(n, 0);
    int i = 0;
    ans[i++] = 1;
    while (i < n) {
      for (int j = 0; j < i; j++) {
        ans[i] = ans[j] * 2 - 1;
        if (ans[i] <= n) {
          i++;
        }
      }
      for (int j = 0; j < i; j++) {
        ans[i] = ans[j] * 2;
        if (ans[i] <= n) {
          i++;
        }
      }
    }
    return ans;
  }

  vector<int> beautifulArray(int n) {
    vector<int> ans(n, 0);
    ans.push_back(10; while (ans.size() < n) {
      vector<int> tmp;
      for (int i = 0; i < ans.size(); i++) {
        if (ans[i] * 2 - 1 <= n) tmp.push_back(ans[i] * 2 - 1);
      }

      for (int i = 0; i < ans.size(); i++) {
        if (ans[i] * 2 <= n) tmp.push_back(ans[i] * 2);
      }
      ans = tmp;
    } return ans;)
  };