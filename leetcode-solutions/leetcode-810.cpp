/*
 * 810. Chalkboard XOR Game
 * 
 * We are given non-negative integers nums[i] which are written on a chalkboard.  Alice and Bob take turns erasing exactly one number from the chalkboard, with Alice starting first.  If erasing a number causes the bitwise XOR of all the elements of the chalkboard to become 0, then that player loses.  (Also, we'll say the bitwise XOR of one element is that element itself, and the bitwise XOR of no elements is 0.)
 * 
 * Example:
 * Input: nums = [1, 1, 2]
 * Output: false
 * Explanation: 
 * Alice has two choices: erase 1 or erase 2. 
 * If she erases 1, the nums array becomes [1, 2]. The bitwise XOR of all the elements of the chalkboard is 1 XOR 2 = 3. Now Bob can remove any element he wants, because Alice will be the one to erase the last element and she will lose. 
 * If Alice erases 2 first, now nums becomes [1, 1]. The bitwise XOR of all the elements of the chalkboard is 1 XOR 1 = 0. Alice will lose.
 * 
 * Note:
 * 1 <= N <= 1000.
 * 0 <= nums[i] <= 2^16.
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    bool xorGame(vector<int>& nums) {
        int totalXor = 0;
        for (int num : nums) totalXor ^= num;

        // 如果全部异或为 0，先手直接获胜
        if (totalXor == 0) return true;

        // 如果存在一个数等于总异或值，先手可以直接擦除它获胜
        for (int num : nums) {
            if (num == totalXor) return true;
        }

        // 否则，胜负由数组长度的奇偶性决定
        // 奇数则先手胜，偶数则先手负
        return nums.size() % 2 == 1;
    }
};