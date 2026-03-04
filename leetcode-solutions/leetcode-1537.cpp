/**
 * 1537. Maximum Score After Splitting a String
 * 
 * Given a string s of zeros and ones, return the maximum score after splitting the string into two non-empty substrings (i.e. left substring and right substring).
 * 
 * The score after splitting a string is the number of zeros in the left substring plus the number of ones in the right substring.
 * 
 * 
 * Example 1:
 * Input: s = "011101"
 * Output: 5 
 * Explanation: 
 * All possible ways of splitting s into two non-empty substrings are:
 * left = "0" and right = "11101", score = 1 + 4 = 5 
 * left = "01" and right = "1101", score = 1 + 3 = 4 
 * left = "011" and right = "101", score = 1 + 2 = 3 
 * left = "0111" and right = "01", score = 1 + 1 = 2 
 * 
 * Example 2:
 * Input: s = "00111"
 * Output: 5
 * Explanation: When left = "00" and right = "111", we get the maximum score = 2 + 3 = 5
 * 
 * Example 3:
 * Input: s = "1111"
 * Output: 3
 * 
 * Constraints:
 * 2 <= s.length <= 1000
 * s[i] is either '0' or '1'.
 * s has at least one '0' and at least one '1'.
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    int maxSum(vector<int>& nums1, vector<int>& nums2) {
        const int MOD = 1e9 + 7;
        int n = nums1.size(), m = nums2.size();
        int i = 0, j = 0;
        long long sum1 = 0, sum2 = 0, ans = 0;

        while (i < n && j < m) {
            if (nums1[i] < nums2[j]) {
                sum1 += nums1[i++];
            } else if (nums1[i] > nums2[j]) {
                sum2 += nums2[j++];
            } else { // common element
                ans += max(sum1, sum2) + nums1[i];
                sum1 = 0;
                sum2 = 0;
                i++;
                j++;
            }
        }

        while (i < n) sum1 += nums1[i++];
        while (j < m) sum2 += nums2[j++];
        ans += max(sum1, sum2);

        return ans % MOD;
    }
};