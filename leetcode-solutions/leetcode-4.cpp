/*
 * Median of two sorted arrays
 */
#include <climits>
#include <vector>
using namespace std;

double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
  vector<int> src{};

  size_t i{0}, j{0};
  while (i < nums1.size() && j < nums2.size()) {
    if (nums1[i] < nums2[j]) {
      src.emplace_back(nums1[i]);
      ++i;
    } else {
      src.emplace_back(nums2[j]);
      ++j;
    }
  }

  while (i < nums1.size()) {
    src.emplace_back(nums1[i]);
    ++i;
  }

  while (j < nums2.size()) {
    src.emplace_back(nums2[j]);
    ++j;
  }

  double ret{0};
  size_t sizeVec = src.size();
  if (sizeVec % 2 == 0)
    ret = (src[sizeVec / 2 - 1] + src[sizeVec / 2]) / 2.0;
  else
    ret = src[sizeVec / 2];

  return ret;
}

/*
  Approach
  1. Since, the arrays have already been provided sorted, the problem is converted to finding the partition point in the
  smaller of the two arrays. Using this idea, we can find the median of the combined sorted array. Partition point can
  be efficiently done using binarysearch.binary search.binarysearch.
  2. Find the partition points mid1mid1mid1 and mid2mid2mid2 in arrays nums1 and nums2 such that elements on the left
  side of the partitions are less than or equal to elements on the right side.
  3. The boundaries of the binary search (low and high) are adjusted based on the comparison of elements in the two
  arrays. The maximum element on the left side of the partition (l1 and l2) and the minimum element on the right side of
  the partition (r1 and r2) can be calculated.
  4. If the conditions l1<=r2 and l2<=r1 are satisfied, it means the partition points are correct, and the median is
  found.
  5. If the total number of elements is odd (n is odd), the median is the maximum of l1 and l2. Else, the median is the
  average of the maximum of l1 and l2 and the minimum of r1 and r2.
  6. If l1 is greater than r2, it means the partition point is on the left side, so adjust the boundaries (high=mid1-1).
  7. If l2 is greater than r1, it means the partition point is on the right side, so adjust the boundaries (low=mid1+1).
 */
double findMedianSortedArrays1(vector<int>& nums1, vector<int>& nums2) {
  int n1 = nums1.size(), n2 = nums2.size();
  int n = n1 + n2;

  if (n1 > n2) {
    return findMedianSortedArrays1(nums2, nums1);
  }

  if (n1 == 0) {
    return n2 % 2 ? nums2[n2 / 2] : (nums2[n2 / 2] + nums2[n2 / 2 - 1]) / 2.0;
  }

  if (n2 == 0) {
    return n1 % 2 ? nums1[n2 / 2] : (nums1[n2 / 2] + nums1[n2 / 2 - 1]) / 2.0;
  }

  int partition = (n + 1) / 2;
  int left1 = 0, right1 = n1;
  int cut1, cut2;
  int l1, r1, l2, r2;

  do {
    cut1 = (left1 + right1) / 2;
    cut2 = partition - cut1;
    l1 = cut1 == 0 ? INT_MIN : nums1[cut1 - 1];
    l2 = cut2 == 0 ? INT_MIN : nums2[cut2 - 1];
    r1 = cut1 >= n1 ? INT_MAX : nums1[cut1];
    r2 = cut2 >= n2 ? INT_MAX : nums2[cut2];

    if (l1 <= r2 && l2 <= r1) {
      return n % 2 ? max(l1, l2) : (max(l1, l2) + min(r1, r2)) / 2.0;
    }

    if (l1 > r2) {
      right1 = cut1 - 1;
    } else {
      left1 = cut1 + 1;
    }
  } while (left1 <= right1);

  return 0.0;
}

double findMedianSortedArrays2(vector<int>& nums1, vector<int>& nums2) {
  int n1 = nums1.size(), n2 = nums2.size();
  if (n1 > n2) {
    return findMedianSortedArrays2(nums2, nums1);
  }

  int low = 0, high = n1, n = n1 + n2;
  int left = (n1 + n2 + 1) >> 1;
  while (low <= high) {
    int mid1 = (low + high) >> 1;
    int mid2 = left - mid1;
    int l1 = INT_MIN, l2 = INT_MIN, r1 = INT_MAX, r2 = INT_MAX;
    if (mid1 < n1) {
      r1 = nums1[mid1];
    }
    if (mid2 < n2) {
      r2 = nums2[mid2];
    }
    if (mid1 - 1 >= 0) {
      l1 = nums1[mid1 - 1];
    }
    if (mid2 - 1 >= 0) {
      l2 = nums2[mid2 - 1];
    }

    if (l1 <= r2 && l2 <= r1) {
      if (n % 2) {
        return max(l1, l2);
      } else {
        return (max(l1, l2) + min(r1, r2)) / 2.0;
      }

    } else if (l1 > r2) {
      high = mid1 - 1;
    } else {
      low = mid1 + 1;
    }
  }

  return 0.0;
}