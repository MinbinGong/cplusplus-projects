/*
Hamming Distance

题目描述
给定两个十进制数字，求它们二进制表示的汉明距离（Hamming distance，即不同位的个数）

题解
对两个数进行按位异或操作，统计有多少个 1 即可。
 */
int hammingDistance(int x, int y) {
  int diff = x ^ y;
  int res = 0;
  while (diff) {
    res += diff & 1;
    diff >>= 1;
  }
  return res;
}