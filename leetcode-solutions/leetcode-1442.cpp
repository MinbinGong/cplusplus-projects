/**
 * 1442. Count Triplets That Can Form Two Arrays of Equal XOR
 * 
 * Given an array of integers arr.
 * 
 * We want to select three indices i, j and k where (0 <= i < j <= k < arr.length).
 * 
 * Let's define a and b as follows:
 * 
 * a = arr[i] ^ arr[i + 1] ^ ... ^ arr[j - 1]
 * b = arr[j] ^ arr[j + 1] ^ ... ^ arr[k]
 * Note that ^ denotes the bitwise-xor operation.
 * 
 * Return the number of triplets (i, j and k) Where a == b.
 * 
 * Example 1:
 * 
 * Input: arr = [2,3,1,6,7]
 * Output: 4
 * Explanation: The triplets are (0,1,2), (0,2,2), (2,3,4) and (2,4,4)
 * 
 * Example 2:
 * 
 * Input: arr = [1,1,1,1,1]
 * Output: 10
 * Explanation: All permutations for arr = [1,1,1,1,1] are: 1, 1, 1, 1, 1.
 * 
 * Example 3:
 * 
 * Input: arr = [2,3]
 * Output: 0
 * Explanation: There are no such triplets.
 * 
 * Example 4:
 * 
 * Input: arr = [1,3,5,7,9]
 * Output: 3
 * Explanation: The triplets are (0,1,3), (0,2,2), (2,3,4)
 * 
 * Example 5:
 * 
 * Input: arr = [7,11,12,9,5,2,7,17,22]
 * Output: 8
 * Explanation: The triplets are (0,1,2), (0,2,2), (2,3,4), (2,4,4), (3,4,4), (0,3,4), (1,3,4), (2,3,4)
 * 
 * Note:
 * 1 <= arr.length <= 300
 * 1 <= arr[i] <= 10^8
 * 
 */
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int countTriplets(vector<int>& arr) {
        int n = arr.size();
        unordered_map<int, int> cnt;  // frequency of prefix XOR values
        unordered_map<int, int> sum;  // sum of indices for each XOR value
        int prefix = 0;
        int ans = 0;
        
        // Initialize: prefix[0] = 0 at index 0
        cnt[0] = 1;
        sum[0] = 0;
        
        for (int i = 1; i <= n; ++i) {
            prefix ^= arr[i-1];  // prefix[i] = XOR of arr[0..i-1]
            int val = prefix;
            
            // For all previous indices a where prefix[a] == val,
            // contribution = (i-1) * cnt[val] - sum[val]
            ans += cnt[val] * (i-1) - sum[val];
            
            cnt[val]++;
            sum[val] += i;
        }
        return ans;
    }
};