/**
 * 1734. Decode XORed Permutation
 * 
 * There is an integer array perm that is a permutation of the first n positive integers, where n is always odd.
 * It was encoded into another integer array encoded of length n - 1, such that encoded[i] = perm[i] XOR perm[i + 1]. For example, if perm = [1,3,2], then encoded = [2,1].
 * Given the encoded array, return the original array perm. It is guaranteed that the answer exists and is unique.
 * 
 * Example 1:
 * Input: encoded = [3,1]
 * Output: [1,2,3]
 * Explanation: If perm = [1,2,3], then encoded = [1 XOR 2,2 XOR 3] = [3,1]
 * 
 * Example 2:
 * Input: encoded = [6,5,4,6]
 * Output: [2,4,1,5,3]
 * 
 * Constraints:
 * 3 <= n < 105
 * n is odd.
 * encoded.length == n - 1
 * 1 <= encoded[i] <= 105
 */
#include <vector>
#include <unordered_set>
using namespace std;

class Solution {
public:
    vector<int> decode(vector<int>& encoded) {
        int n = encoded.size() + 1; // n 是奇数
        int total = 0;
        // 计算 1 到 n 的异或
        for (int i = 1; i <= n; ++i) {
            total ^= i;
        }
        int oddXor = 0;
        // 计算 encoded 中所有奇数下标（1,3,5...）的异或
        for (int i = 1; i < encoded.size(); i += 2) {
            oddXor ^= encoded[i];
        }
        vector<int> perm(n);
        perm[0] = total ^ oddXor; // 得到第一个元素
        for (int i = 1; i < n; ++i) {
            perm[i] = perm[i-1] ^ encoded[i-1];
        }
        return perm;
    }
};