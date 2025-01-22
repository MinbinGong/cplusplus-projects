/*
 * leetcode-307
 * Range Sum Query - Mutable
 * 
 * Given an integer array nums, handle multiple queries of the following types:
 * 1. Update the value of an element in nums.
 * 2. Calculate the sum of the elements of nums between indices left and right inclusive
 *   where left <= right.
 * 3. Implement the NumArray class:
 * 
 * NumArray(int[] nums) Initializes the object with the integer array nums.
 * void update(int index, int val) Updates the value of nums[index] to be val.
 * int sumRange(int left, int right) Returns the sum of the elements of nums between indices left and right inclusive (i.e. nums[left] + nums[left + 1] + ... + nums[right]).
 */
#include <vector>
using namespace std;
class NumArray {
public:
    NumArray(vector<int>& nums) {
        n = nums.size();
        tree.resize(2 * n);
        for (int i = n; i < 2 * n; ++i) {
            tree[i] = nums[i - n];
        }
        for (int i = n - 1; i > 0; --i) {
            tree[i] = tree[2 * i] + tree[2 * i + 1];
        }
    }
    void update(int index, int val) {
        index += n;
        tree[index] = val;
        while (index > 0) {
            int left = index, right = index;
            if (index % 2 == 0) {
                right = index + 1;
            } else {
                left = index - 1;
            }
            tree[index / 2] = tree[left] + tree[right];
            index /= 2;
        }
    }
    int sumRange(int left, int right) {
        left += n;
        right += n;
        int sum = 0;
        while (left <= right) {
            if (left % 2 == 1) {
                sum += tree[left];
                ++left;
            }
            if (right % 2 == 0) {
                sum += tree[right];
                --right;
            }
            left /= 2;
            right /= 2;
        }
        return sum;
    }
private:
    vector<int> tree;
    int n;
};