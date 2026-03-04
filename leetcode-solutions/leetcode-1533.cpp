/**
 * 1533. Find the Index of the Large Integer
 *
 * We have an integer array arr, where all the integers in arr are equal except for one integer which is larger than the
 * rest of the integers. You will not be given direct access to the array, instead, you will have an API ArrayReader
 * which have the following functions:
 *
 * int compareSub(int l, int r, int x, int y): where 0 <= l, r, x, y < ArrayReader.length(), l <= r and x <= y. The
 * function compares the sum of sub-array arr[l..r] with the sum of the sub-array arr[x..y] and returns: 1 if
 * arr[l]+arr[l+1]+...+arr[r] > arr[x]+arr[x+1]+...+arr[y]. 0 if arr[l]+arr[l+1]+...+arr[r] ==
 * arr[x]+arr[x+1]+...+arr[y]. -1 if arr[l]+arr[l+1]+...+arr[r] < arr[x]+arr[x+1]+...+arr[y].
 *
 * Example 1:
 * Input: arr = [7,7,7,7,10,7,7,7]
 * Output: 4
 * Explanation: The following calls to the API
 * reader.compareSub(0, 0, 1, 1) // returns 0
 * reader.compareSub(2, 2, 4, 4) // returns -1
 * reader.compareSub(0, 1, 2, 2) // returns 1
 *
 * Example 2:
 * Input: arr = [6,6,12]
 * Output: 2
 *
 *
 * Constraints:
 * 2 <= arr.length <= 10^5
 * 0 <= arr[i] <= 10^9
 * All the elements of arr are equal except for one element which is larger than the rest of the elements.
 *
 */
#include <algorithm>
#include <climits>
#include <string>
#include <vector>

using namespace std;

/**
 * // This is the ArrayReader's API interface.
 * // You should not implement it, or speculate about its implementation
 */
class ArrayReader {
 public:
  // Compares the sum of arr[l..r] with the sum of arr[x..y]
  // return 1 if sum(arr[l..r]) > sum(arr[x..y])
  // return 0 if sum(arr[l..r]) == sum(arr[x..y])
  // return -1 if sum(arr[l..r]) < sum(arr[x..y])
  int compareSub(int l, int r, int x, int y);

  // Returns the length of the array
  int length();
};

class Solution {
 public:
  int getIndex(ArrayReader& reader) {
    int n = reader.length();
    int left = 0, right = n - 1;

    while (left < right) {
      int mid1, mid2;
      int len = right - left + 1;

      if (len % 2 == 0) {
        // 偶数长度：平分
        mid1 = left + len / 2 - 1;
        mid2 = left + len / 2;
      } else {
        // 奇数长度：中间元素作为公共部分
        mid1 = mid2 = left + len / 2;
      }

      int res = reader.compareSub(left, mid1, mid2, right);

      if (res == 1) {
        // 最大整数在左半部分 [left, mid1]
        right = mid1;
      } else if (res == -1) {
        // 最大整数在右半部分 [mid2, right]
        left = mid2;
      } else {
        // 相等，说明中间元素就是最大的
        return mid1;
      }
    }

    return left;
  }
};