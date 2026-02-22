/*
 * Set Mismatch
 *
 * The set S originally contains numbers from 1 to n. But unfortunately, due to the data error, one of the numbers in the set got duplicated to another number in the set, which results in repetition of one number and loss of another number.
 *
 * Given an array nums representing the data status of this set after the error. Your task is to firstly find the number occurs twice and then find the number that is missing. Return them in the form of an array.
 *
 * Note:
 *
 * The given array size will in the range [2, 10000].
 * The given array's numbers won't have any order.
 *
 */
#include <vector>
using namespace std;

vector<int> findErrorNums1(vector<int>& nums) {
    int dup = -1, miss = -1;
    for (int i = 0; i < nums.size(); i++) {
        int idx = abs(nums[i]) - 1;
        if (nums[idx] < 0) {
            dup = abs(nums[i]);
        } else {
            nums[idx] = -nums[idx];
        }
    }
    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] > 0) {
            miss = i + 1;
            break;
        }
    }
    return {dup, miss};
}

vector<int> findErrorNums2(vector<int>& nums) {
    int n = nums.size();
    int xorAll = 0;
    for (int i = 1; i <= n; i++) xorAll ^= i;
    for (int num : nums) xorAll ^= num; // now xorAll = dup ^ missing

    // find rightmost set bit
    int rightmostBit = xorAll & -xorAll;
    int xorSet = 0, xorNotSet = 0;

    for (int i = 1; i <= n; i++) {
        if (i & rightmostBit) xorSet ^= i;
        else xorNotSet ^= i;
    }
    for (int num : nums) {
        if (num & rightmostBit) xorSet ^= num;
        else xorNotSet ^= num;
    }

    // now xorSet and xorNotSet are the two numbers (dup and missing)
    // scan nums to find which is duplicate
    for (int num : nums) {
        if (num == xorSet) return {xorSet, xorNotSet};
    }
    return {xorNotSet, xorSet};
}

vector<int> findErrorNums3(vector<int>& nums) {
    long long n = nums.size();
    long long sum_n = n*(n+1)/2;
    long long sum_sq_n = n*(n+1)*(2*n+1)/6;
    long long sum = 0, sum_sq = 0;
    for (int num : nums) {
        sum += num;
        sum_sq += (long long)num * num;
    }
    long long diff = sum - sum_n;              // dup - miss
    long long diff_sq = sum_sq - sum_sq_n;      // dup^2 - miss^2 = (dup - miss)(dup + miss)
    long long sum_dup_miss = diff_sq / diff;    // dup + miss
    int dup = (diff + sum_dup_miss) / 2;
    int miss = sum_dup_miss - dup;
    return {dup, miss};
}