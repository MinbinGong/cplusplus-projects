/*
 * Maxinum Gap
 * Given an integer array nums, return the maximum difference between two
 * successive elements in its sorted form. If the array contains less than two
 * elements, return 0.
 *
 * You must write an algorithm that runs in linear time and uses linear extra
 * space.
 */
#include <algorithm>
#include <vector>
using namespace std;

int maximumGap(vector<int>& nums) {
  long long n = nums.size();
  int maxi = *max_element(nums.begin(), nums.end());
  int mini = *min_element(nums.begin(), nums.end());

  if (maxi == mini) {
    return 0;
  }

  vector<int> bucketLargest(n, INT_MIN);
  vector<int> bucketSmallest(n, INT_MAX);

  for (int i = 0; i < n; i++) {
    int index = (((nums[i] - mini) * (n - 1)) / (maxi - mini));
    bucketLargest[index] = max(bucketLargest[index], nums[i]);
    bucketSmallest[index] = min(bucketSmallest[index], nums[i]);
  }

  int largestGap = 0;
  int i = 0, j = 1;
  while (j < n) {
    if (bucketLargest[j] == INT_MIN) {
      j++;
    } else if (bucketLargest[i] == INT_MIN) {
      i++;
    } else {
      largestGap = max(largestGap, bucketSmallest[j] - bucketLargest[i]);
      i++;
      j++;
    }
  }
  return largestGap;
}

int maximumGap1(vector<int>& nums) {
  int n = nums.size();
  sort(begin(nums), end(nums));
  int diff = 0, ans = 0;
  for (int i = 1; i < n; i++) {
    diff = nums[i] - nums[i - 1];
    ans = max(diff, ans);
  }
  return ans;
}