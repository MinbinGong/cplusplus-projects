/**
 * 1538. Guess the Majority in a Hidden Array
 *
 * We have an integer array nums, where all the integers in nums are 0 or 1. You will not be given direct access to the
 * array, instead, you will have an API ArrayReader which have the following functions:
 *
 * int query(int a, int b, int c, int d): where 0 <= a < b < c < d < ArrayReader.length(). The function returns the
 * distribution of the value of the 4 elements and returns: 4 : if the values of the 4 elements are the same (0 or 1).
 * 2 : if three elements have a value equal to 0 and one element has value equal to 1 or vice versa.
 * 0 : if two element have a value equal to 0 and two elements have a value equal to 1.
 * int length(): Returns the size of the array.
 * You are allowed to call query() 2 * n times at most where n is equal to ArrayReader.length().
 *
 * Return any index of the most frequent value in nums, in case of tie, return -1.
 *
 *
 * Example 1:
 * Input: nums = [0,1,1,0,1,1,1,0]
 * Output: 5
 * Explanation: The following calls to the API
 * reader.length() // returns 8
 * reader.query(0,1,2,3) // returns 2
 * reader.query(4,5,6,7) // returns 4
 * The most frequent value is 1, it appears 5 times in nums which is greater than any other value.
 *
 * Example 2:
 * Input: nums = [0,0,1,1,0]
 * Output: 0
 *
 * Example 3:
 * Input: nums = [1,1,1,0]
 * Output: -1
 * Explanation: The only possible value for nums[3] is 0.
 *
 * Constraints:
 * 5 <= nums.length <= 10^5
 * 0 <= nums[i] <= 1
 *
 */
#include <vector>
using namespace std;

/**
/**
 * // This is the ArrayReader's API interface.
 * // You should not implement it, or speculate about its implementation
 */
class ArrayReader {
 public:
  // Compares the distribution of four elements at indices a,b,c,d.
  // Returns:
  //   4 if all four values are the same (0 or 1)
  //   2 if three elements are the same (3-1 split)
  //   0 if two are 0 and two are 1 (even split)
  int query(int a, int b, int c, int d);

  // Returns the length of the array
  int length();
};

class Solution {
 public:
  int guessMajority(ArrayReader& reader) {
    int n = reader.length();

    // Baseline: compare the first four elements
    int base = reader.query(0, 1, 2, 3);

    // Counters: sameGroup = indices matching the baseline pattern,
    // diffGroup = indices that differ.
    int sameGroup = 1;  // indices 0,1,2,3 are our reference group, count one of them (index 3) as reference
    int diffGroup = 0;
    int diffIndex = -1;  // store an index from the differing group

    // Process indices 4..n-1 by comparing with fixed first three indices
    for (int i = 4; i < n; ++i) {
      if (reader.query(0, 1, 2, i) == base) {
        sameGroup++;
      } else {
        diffGroup++;
        diffIndex = i;
      }
    }

    // Now we need to classify the first three indices (0,1,2)
    // To do this, we use a second baseline with index 4
    int base2 = reader.query(0, 1, 2, 4);  // 4 is already classified as same/diff

    // Helper lambda to test index j (0 ≤ j ≤ 2) by replacing it with index 4
    // We compare query(0,1,2,4) with query of a set that excludes j and includes 4
    for (int j = 0; j < 3; ++j) {
      // The three indices to query: all from {0,1,2,4} except j
      int a, b, c;
      if (j == 0) {
        a = 1;
        b = 2;
        c = 4;
      } else if (j == 1) {
        a = 0;
        b = 2;
        c = 4;
      } else {  // j == 2
        a = 0;
        b = 1;
        c = 4;
      }
      if (reader.query(a, b, c, 4) == base2) {
        sameGroup++;
      } else {
        diffGroup++;
        diffIndex = j;
      }
    }

    // Final decision
    if (sameGroup == diffGroup) {
      return -1;
    }
    return (sameGroup > diffGroup) ? 3 : diffIndex;
  }
};