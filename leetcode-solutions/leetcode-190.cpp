/*
Reverse Bits

题目描述
给定一个十进制整数，输出它在二进制下的翻转结果。

题解
使用算术左移和右移，可以很轻易地实现二进制的翻转。
 */
#include <cstdint>

uint32_t reverseBits(uint32_t n) {
  uint32_t ans = 0;
  for (int i = 0; i < 32; ++i) {
    ans <<= 1;
    ans += n & 1;
    n >>= 1;
  }
  return ans;
}