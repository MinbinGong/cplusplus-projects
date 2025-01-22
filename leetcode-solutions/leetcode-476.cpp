/*
 * leetcode-476
 * Number Complement
 * 
 * 题目描述
 * 给定一个正整数，输出它的补数。补数是对该数的二进制表示取反。
 */
#include <cstdint>

uint32_t findComplement(uint32_t num) {
    uint32_t ans = 0;
    for (int i = 0; i < 32; ++i) {
        ans <<= 1;
        ans += !(num & 1);
        num >>= 1;
    }
    return ans;