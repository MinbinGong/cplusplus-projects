/*
Factorial Trailing Zeros

题目描述
给定一个非负整数，判断它的阶乘结果的结尾有几个 0。

题解
每个尾部的 0 由 2 × 5 = 10 而来，因此我们可以把阶乘的每一个元素拆成质数相乘，统计有
多少个 2 和 5。明显的，质因子 2 的数量远多于质因子 5 的数量，因此我们可以只统计阶乘结果
里有多少个质因子 5。
 */

int trailingZeros(int n) { return n == 0 ? 0 : n / 5 + trailingZeros(n / 5); }