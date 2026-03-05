/*
 * 1577. Number of Ways Where Square of Number Is Equal to Product of Two Numbers
 *
 * Given two arrays of integers nums1 and nums2, return the number of triplets formed (type 1 and type 2) under the following rules:
 * 
 * Type 1: Triplet (i, j, k) if nums1[i]2 == nums2[j] * nums2[k] where 0 <= i < nums1.length and 0 <= j < k < nums2.length.
 * Type 2: Triplet (i, j, k) if nums2[i]2 == nums1[j] * nums1[k] where 0 <= i < nums2.length and 0 <= j < k < nums1.length.
 * 
 * Example 1:
 * Input: nums1 = [7,4], nums2 = [5,2,8,9]
 * Output: 1
 * Explanation: Type 1: (1, 0, 2), nums1[1]2 = nums2[0] * nums2[2]. (42 = 2 * 8). 
 * 
 * Example 2:
 * Input: nums1 = [1,1], nums2 = [1,1,1]
 * Output: 9
 * Explanation: All Triplets are valid, because 12 = 1 * 1.
 * Type 1: (0, 0, 1), (0, 0, 2), (0, 1, 2), (1, 0, 1), (1, 0, 2). 
 * Type 2: (0, 0, 1), (1, 0, 1), (2, 0, 1).
 * 
 * Example 3:
 * Input: nums1 = [7,7,8,3], nums2 = [1,2,9,7]
 * Output: 2
 * Explanation: There are 2 valid triplets.
 * Type 1: (3, 0, 2). nums1[3]2 = nums2[0] * nums2[2]. (82 = 7 * 7).
 * Type 2: (3, 0, 1). nums2[3]2 = nums1[0] * nums1[1]. (72 = 7 * 7).
 * 
 * Constraints:
 * 1 <= nums1.length, nums2.length <= 1000
 * 1 <= nums1[i], nums2[i] <= 10^4
 * 
 */
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int numTriplets(vector<int>& nums1, vector<int>& nums2) {
        return countTriplets(nums1, nums2) + countTriplets(nums2, nums1);
    }

private:
    int countTriplets(const vector<int>& A, const vector<int>& B) {
        // count all index pairs (j, k) with j <= k in B and their product
        unordered_map<long long, int> prodCount;
        int n = B.size();
        for (int j = 0; j < n; ++j) {
            for (int k = j; k < n; ++k) {
                long long product = static_cast<long long>(B[j]) * B[k];
                ++prodCount[product];
            }
        }
        
        // count how many squares from A match those products
        int ans = 0;
        for (int num : A) {
            long long square = static_cast<long long>(num) * num;
            auto it = prodCount.find(square);
            if (it != prodCount.end()) {
                ans += it->second;
            }
        }
        return ans;
    }
};