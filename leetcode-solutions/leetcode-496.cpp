/*
 *  Next Greater Element I
 *
 *  You are given two integer arrays nums1 and nums2 both of unique elements, where nums1 is a subset of nums2.
 *
 *  Find all the next greater numbers for nums1's elements in the corresponding places of nums2.
 *
 *  The Next Greater Number of a number x in nums1 is the first greater number to its right in nums2. If it does not exist, return -1 for this number.
 *
 *  Constraints:
 *  1 <= nums1.length <= nums2.length <= 1000
 *  0 <= nums1[i], nums2[i] <= 104
 *  All integers in nums1 and nums2 are unique.
 *  All the integers of nums1 also appear in nums2.
 * 
 */
#include <vector>
#include <unordered_map>
#include <stack>
using namespace std;

class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> nextGreater;
        stack<int> st;
        for (int num : nums2) {
            while (!st.empty() && st.top() < num) {
                nextGreater[st.top()] = num;
                st.pop();
            }
            st.push(num);
        }
        vector<int> res;
        for (int num : nums1) {
            res.push_back(nextGreater.count(num) ? nextGreater[num] : -1);
        }
        return res;
    }
};