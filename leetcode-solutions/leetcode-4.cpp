/*
 * Median of two sorted arrays
 */
#include <vector>
using namespace std;

double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2) {
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