/*
Shuffle an Array

题目描述
给定一个数组，要求实现两个指令函数。第一个函数“shuﬄe”可以随机打乱这个数组，第
二个函数“reset”可以恢复原来的顺序。

题解
我们采用经典的 Fisher-Yates 洗牌算法，原理是通过随机交换位置来实现随机打乱，有正向
和反向两种写法，且实现非常方便。注意这里“reset”函数以及类的构造函数的实现细节。
 */
#include <random>
#include <vector>
using namespace std;

vector<int> shuffle(vector<int>& origin) {
  if (origin.empty()) {
    return {};
  }

  vector<int> shuffled(origin);
  int n = shuffled.size();
  for (int i = n - 1; i >= 0; --i) {
    swap(shuffled[i], shuffled[rand() % (i + 1)]);
  }
  return shuffled;
}