/**
 * 1390. Four Divisors
 * 
 * Given an integer array nums, return the sum of divisors of the integers in that array that have exactly four divisors.
 * 
 * If there is no such integer in the array, return 0.
 * 
 * Example 1:
 * Input: nums = [21,4,7]
 * Output: 32
 * Explanation:
 * 21 has 4 divisors: 1, 3, 7, 21
 * 4 has 3 divisors: 1, 2, 4
 * 7 has 2 divisors: 1, 7
 * The answer is the sum of divisors of 21 only.
 * 
 * Example 2:
 * Input: nums = [21,21]
 * Output: 64
 * 
 * Example 3:
 * Input: nums = [1,2,3,4,5]
 * Output: 0
 * 
 * Note:
 * 1 <= nums.length <= 10^4
 * 1 <= nums[i] <= 10^5
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    int sumFourDivisors(vector<int>& nums) {
        int total = 0;
        for (int num : nums) {
            int cnt = 0, sum = 0;
            // iterate up to sqrt(num) to find all divisors
            for (int i = 1; i * i <= num; ++i) {
                if (num % i == 0) {
                    cnt++;
                    sum += i;
                    if (i != num / i) {   // avoid double counting square root
                        cnt++;
                        sum += num / i;
                    }
                }
                if (cnt > 4) break;        // early stop if more than 4 divisors
            }
            if (cnt == 4) total += sum;
        }
        return total;
    }
};