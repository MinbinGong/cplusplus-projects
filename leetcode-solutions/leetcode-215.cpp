/*
题目描述
在一个未排序的数组中，找到第 k 大的数字

题解
快速选择一般用于求解 k-th Element 问题，可以在 O(n) 时间复杂度，O(1) 空间复杂度完成求解工作。
快速选择的实现和快速排序相似，不过只需要找到第 k 大的枢（pivot）即可，不需要对其左右再进行排序。
与快速排序一样，快速选择一般需要先打乱数组，否则最坏情况下时间复杂度为 O(n2 )
 */
#include <vector>
using namespace std;

int quickSelection(vector<int>& nums, int l, int r) {
    int i = l + 1, j = r;
    while (true) {
        while (i < r && nums[i] <= nums[l]) {
            ++i;
        }
        while (l < j && nums[j] >= nums[l]) {
            --j;
        }
        if (i >= j) {
            break;
        }
        swap(nums[i], nums[j]);
    }
    swap(nums[l], nums[j]);
    return j;
}

int findKLargest(vector<int>& nums, int k) {
    int l = 0, r = nums.size() - 1, target = nums.size() - k;
    while (l < r) {
        int mid = quickSelection(nums, l, r);
        if (mid == target) {
            return nums[mid];
        }

        if (mid < target) {
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    return nums[l];
}