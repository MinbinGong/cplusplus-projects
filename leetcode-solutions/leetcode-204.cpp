/*
Count Primes

题目描述
给定一个数字 n，求小于 n 的质数的个数。

题解
埃拉托斯特尼筛法（Sieve of Eratosthenes，简称埃氏筛法）是非常常用的，判断一个整数是
否是质数的方法。并且它可以在判断一个整数 n 时，同时判断所小于 n 的整数，因此非常适合这
道题。其原理也十分易懂：从 1 到 n 遍历，假设当前遍历到 m，则把所有小于 n 的、且是 m 的倍
数的整数标为和数；遍历完成后，没有被标为和数的数字即为质数。
 */
#include <cmath>
#include <vector>
using namespace std;

int countPrime(int n) {
  if (n <= 2) {
    return 0;
  }
  vector<bool> prime(n, true);
  int i = 3, sqrtn = sqrt(n), count = n;
  while (i <= sqrtn) {
    for (int j = i * i; j < n; j += 2 * i) {
      if (prime[j]) {
        --count;
        prime[j] = false;
      }
    }

    do {
      i += 2;
    } while (i <= sqrtn && !prime[i]);
  }
  return count;
}