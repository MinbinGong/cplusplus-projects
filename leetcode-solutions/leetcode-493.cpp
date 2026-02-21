/*
 * Reverse Pairs
 *
 *  Given an integer array nums, return the number of reverse pairs in the array.
 *
 *  A reverse pair is a pair (i, j) where:
 *
 *  0 <= i < j < nums.length and
 *  nums[i] > 2 * nums[j].
 *
 *  Constraints:
 *  1 <= nums.length <= 5 * 104
 *  -231 <= nums[i] <= 231 - 1
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    int reversePairs(vector<int>& nums) {
        return mergeSort(nums, 0, nums.size() - 1);
    }

private:
    int mergeSort(vector<int>& nums, int l, int r) {
        if (l >= r) return 0;
        int mid = l + (r - l) / 2;
        int count = mergeSort(nums, l, mid) + mergeSort(nums, mid + 1, r);

        // Count reverse pairs crossing the two halves
        int j = mid + 1;
        for (int i = l; i <= mid; ++i) {
            while (j <= r && nums[i] > 2LL * nums[j]) ++j;
            count += (j - (mid + 1));
        }

        // Merge the two sorted halves
        vector<int> temp(r - l + 1);
        int i = l, k = mid + 1, t = 0;
        while (i <= mid && k <= r) {
            if (nums[i] < nums[k]) temp[t++] = nums[i++];
            else temp[t++] = nums[k++];
        }
        while (i <= mid) temp[t++] = nums[i++];
        while (k <= r) temp[t++] = nums[k++];
        for (int idx = 0; idx < temp.size(); ++idx) {
            nums[l + idx] = temp[idx];
        }
        return count;
    }
};