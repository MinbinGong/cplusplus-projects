/**
 * 1803. Count Pairs With XOR in a Range
 * 
 * Given a (0-indexed) integer array nums and two integers low and high, return the number of nice pairs.
 * 
 * A nice pair is a pair (i, j) where 0 <= i < j < nums.length and low <= (nums[i] XOR nums[j]) <= high.
 * 
 *  
 * 
 * Example 1:
 * 
 * Input: nums = [1,4,2,7], low = 2, high = 6
 * Output: 6
 * Explanation: All nice pairs (i, j) are as follows:
 *    - (0, 1): nums[0] XOR nums[1] = 5 
 *    - (0, 2): nums[0] XOR nums[2] = 3
 *    - (0, 3): nums[0] XOR nums[3] = 6
 *    - (1, 2): nums[1] XOR nums[2] = 6
 *    - (1, 3): nums[1] XOR nums[3] = 3
 *    - (2, 3): nums[2] XOR nums[3] = 5
 * Example 2:
 * 
 * Input: nums = [9,8,4,2,1], low = 5, high = 14
 * Output: 8
 * Explanation: All nice pairs (i, j) are as follows:
 *    - (0, 2): nums[0] XOR nums[2] = 13
 *    - (0, 3): nums[0] XOR nums[3] = 11
 *    - (0, 4): nums[0] XOR nums[4] = 8
 *    - (1, 2): nums[1] XOR nums[2] = 12
 *    - (1, 3): nums[1] XOR nums[3] = 10
 *    - (1, 4): nums[1] XOR nums[4] = 9
 *    - (2, 3): nums[2] XOR nums[3] = 6
 *    - (2, 4): nums[2] XOR nums[4] = 5
 *  
 * 
 * Constraints:
 * 
 * 1 <= nums.length <= 2 * 104
 * 1 <= nums[i] <= 2 * 104
 * 1 <= low <= high <= 2 * 104
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    int countPairs(vector<int>& nums, int low, int high) {
        // number of pairs with XOR in [low, high] = 
        // (pairs with XOR <= high) - (pairs with XOR <= low-1)
        return countLessEqual(nums, high) - countLessEqual(nums, low - 1);
    }

private:
    struct TrieNode {
        TrieNode* next[2];
        int cnt;
        TrieNode() {
            next[0] = next[1] = nullptr;
            cnt = 0;
        }
    };

    // count pairs (i < j) such that (nums[i] XOR nums[j]) <= limit
    int countLessEqual(vector<int>& nums, int limit) {
        if (limit < 0) return 0;
        TrieNode* root = new TrieNode();
        int ans = 0;
        for (int x : nums) {
            ans += query(root, x, limit);
            insert(root, x);
        }
        // memory deallocation is not necessary for a single test case
        return ans;
    }

    void insert(TrieNode* root, int x) {
        TrieNode* node = root;
        for (int i = 30; i >= 0; --i) {
            int bit = (x >> i) & 1;
            if (!node->next[bit]) node->next[bit] = new TrieNode();
            node = node->next[bit];
            node->cnt++;
        }
    }

    int query(TrieNode* root, int x, int limit) {
        TrieNode* node = root;
        int res = 0;
        for (int i = 30; i >= 0; --i) {
            int a = (x >> i) & 1;      // bit of x
            int b = (limit >> i) & 1;   // bit of limit
            if (b == 1) {
                // if we choose XOR bit 0 at this position, all numbers in that branch
                // are already smaller than limit → add them
                if (node->next[a]) res += node->next[a]->cnt;
                // then continue with the branch where XOR bit = 1 to match limit
                node = node->next[a ^ 1];
            } else {
                // must have XOR bit = 0 to stay ≤ limit
                node = node->next[a];
            }
            if (!node) break;
        }
        if (node) res += node->cnt;     // numbers whose XOR equals limit exactly
        return res;
    }
};
