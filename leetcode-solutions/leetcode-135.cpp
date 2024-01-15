/*
题目描述
一群孩子站成一排，每一个孩子有自己的评分。现在需要给这些孩子发糖果，规则是如果一
个孩子的评分比自己身旁的一个孩子要高，那么这个孩子就必须得到比身旁孩子更多的糖果；所
有孩子至少要有一个糖果。求解最少需要多少个糖果。

题解
虽然这一道题也是运用贪心策略，但我们只需要简单的两次遍历即可：把所有孩子的糖果数初始化为 1；
先从左往右遍历一遍，如果右边孩子的评分比左边的高，则右边孩子的糖果数更新为左边孩子的
糖果数加 1；再从右往左遍历一遍，如果左边孩子的评分比右边的高，且左边孩子当前的糖果数
不大于右边孩子的糖果数，则左边孩子的糖果数更新为右边孩子的糖果数加 1。通过这两次遍历，
分配的糖果就可以满足题目要求了。这里的贪心策略即为，在每次遍历中，只考虑并更新相邻一
侧的大小关系。
*/
#include <vector>
using namespace std;

int candy(vector<int>& ratings) {
  vector<int> candies(ratings.size(), 1);
  for (size_t i = 0; i < ratings.size(); ++i) {
    if (ratings[i] > ratings[i - 1] && candies[i] <= candies[i - 1]) {
      candies[i] = candies[i - 1] + 1;
    } else if (ratings[i] < ratings[i - 1] && candies[i] >= candies[i - 1]) {
      candies[i - 1] = candies[i] + 1;
    }
  }

  for (int j = ratings.size() - 2; j >= 0; --j) {
    if (ratings[j] > ratings[j + 1] && candies[j] <= candies[j + 1]) {
      candies[j] = candies[j + 1] + 1;
    } else if (ratings[j] < ratings[j + 1] && candies[j] >= candies[j + 1]) {
      candies[j + 1] = candies[j] + 1;
    }
  }

  int ans = 0;
  for (const auto i : candies) ans += i;
  return ans;
}

int candy2(vector<int>& ratings) {
  int size = ratings.size();
  if (size < 2) {
    return size;
  }

  vector<int> num(size, 1);
  for (int i = 1; i < size; i++) {
    if (ratings[i] > ratings[i - 1]) {
      nums[i] = nums[i - 1] + 1;
    }
  }
  for (int i = size - 1; i > 0; i--) {
    if (ratings[i] < ratings[i - 1]) {
      num[i - 1] = max(num[i - 1], num[i] + 1);
    }
  }

  int res = 0;
  for (auto item : num) {
    res += item;
  }

  return res;
}