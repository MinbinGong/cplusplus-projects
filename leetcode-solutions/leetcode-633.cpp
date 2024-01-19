/*
 * Sum of Square Numbers
 *
 * Given a non-negative integer c, decide whether there're two integers a and b such that a2 + b2 = c
 */
#include <cmath>
using namespace std;

bool judgeSquareSum(int c) {
    if (c == 1) return true;

    long long left = 0, right = sqrt(c);
    while (left <= right) {
        long long sum = (left * left) + (right * right);
        if (sum == c) return true;
        else if (sum < c) left++;
        else right--;
    }
    return false;
}
