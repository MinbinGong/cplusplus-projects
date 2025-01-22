/*
 * leetcode-693.cpp
 * Binary Number with Alternating Bits
 * 
 * Given a positive integer, check whether it has alternating bits: namely,
 * if two adjacent bits will always have different values.
 * 
 * Example 1:
 * Input: 5
 * Output: True
 * Explanation:
 * The binary representation of 5 is: 101
 * 
 */
#include <cstdint>
#include <iostream>
using namespace std;
class Solution {
public:
    bool hasAlternatingBits(int n) {
        int64_t ans = 0;
        int64_t tmp = n;
        while (tmp) {
            ans <<= 1;
            ans += tmp & 1;
            tmp >>= 1;
        }
        return (ans & (ans >> 1)) == 0;
    }
};