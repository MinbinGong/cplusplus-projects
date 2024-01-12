/*
  Random Pick with Weight

  题目描述
  给定一个数组，数组每个位置的值表示该位置的权重，要求按照权重的概率去随机采样。

  题解
  我们可以先使用 partial_sum 求前缀和（即到每个位置为止之前所有数字的和）
  ，这个结果
  对于正整数数组是单调递增的。每当需要采样时，我们可以先随机产生一个数字，然后使用二分
  法查找其在前缀和中的位置，以模拟加权采样的过程。这里的二分法可以用 lower_bound 实现。
  以样例为例，
  权重数组 [1,3] 的前缀和为 [1,4]。
  如果我们随机生成的数字为 1，那么 lower_bound
  返回的位置为 0；如果我们随机生成的数字是 2、3、4，那么 lower_bound 返回的位置为 1。
 */
#include <algorithm>
#include <numeric>
#include <random>
#include <vector>
using namespace std;

int pickIndex(vector<int>& weights) {
  vector<int> sums(weights);
  
  partial_sum(sums.begin(), sums.end(), sums.begin());
  
  int pos = (rand() % sums.back()) + 1;
  return lower_bound(sums.begin(), sums.end(), pos) - sums.begin();
}