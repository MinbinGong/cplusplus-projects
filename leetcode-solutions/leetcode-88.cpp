/*
 * Merge Sorted Array
 * 题目描述
 * 给定两个有序数组，把两个数组合并为一个。
 *
 * 题解
 * 因为这两个数组已经排好序，我们可以把两个指针分别放在两个数组的末尾，即 nums1 的
 * m − 1 位和 nums2 的 n − 1 位。每次将较大的那个数字复制到 nums1 的后边，然后向前移动一位。
 * 因为我们也要定位 nums1 的末尾，所以我们还需要第三个指针，以便复制。
 * 在以下的代码里，我们直接利用 m 和 n 当作两个数组的指针，再额外创立一个 pos 指针，起
 * 始位置为 m + n − 1。每次向前移动 m 或 n 的时候，也要向前移动 pos。这里需要注意，如果 nums1
 * 的数字已经复制完，不要忘记把 nums2 的数字继续复制；如果 nums2 的数字已经复制完，剩余
 * nums1 的数字不需要改变，因为它们已经被排好序
 */
#include <vector>
using namespace std;

void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    int pos = m--+n---1;
    while(m >= 0 && n >= 0) {
        nums1[pos--] = nums1[m] > nums2[n] ? nums1[m--] : nums2[n--];
    }

    while (n >= 0) {
        nums1[pos--] = nums2[n--];
    }
}
