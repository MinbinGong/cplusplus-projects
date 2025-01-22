/*
 * leetcode-870
 * Advantage Shuffle
 * 
 * You are given two integer arrays nums1 and nums2 both of the same length.
 * The advantage of nums1 with respect to nums2 is the number of indices i for which nums1[i] > nums2[i].
 * Return any permutation of nums1 that maximizes its advantage with respect to nums2.
 */
#include <algorithm>
#include <vector>
using namespace std;
vector<int> advantageCount(vector<int>& nums1, vector<int>& nums2) {
    sort(nums1.begin(), nums1.end());
    vector<int> ans;
    for (int i = 0; i < nums2.size(); ++i) {
        auto it = upper_bound(nums1.begin(), nums1.end(), nums2[i]);
        if (it == nums1.end()) {
            ans.push_back(nums1[0]);
            nums1.erase(nums1.begin());
        } else {
            ans.push_back(*it);
            nums1.erase(it);
        }
    }
    return ans;
}