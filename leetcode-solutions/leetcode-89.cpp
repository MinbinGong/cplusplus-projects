/*
 * An n-bit gray code sequence is a sequence of 2n integers where:
 *
 * Every integer is in the inclusive range [0, 2n - 1],
 * The first integer is 0,
 * An integer appears no more than once in the sequence,
 * The binary representation of every pair of adjacent integers differs by exactly one bit, and
 * The binary representation of the first and last integers differs by exactly one bit.
 *
 * Given an integer n, return any valid n-bit gray code sequence.
 */
#include <vector>
using namespace std;

vector<int> grayCode(int n) {
    vector<int> ans(1<<n);

    for (int i = 0; i < (1<<n); ++i) {
        ans[i] = i ^ (i >> 1);
    }

    return ans;
}
