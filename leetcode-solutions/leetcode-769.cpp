/*
 * Max Chunks To Make Sorted
 *
 * Given an array arr that is a permutation of [0, 1, ..., arr.length - 1], we split the array into some number of "chunks" (partitions), and individually sort each chunk.  After concatenating them, the result equals the sorted array.
 * 
 * What is the most number of chunks we could have made?
 * 
 * Example 1:
 * Input: arr = [4,3,2,1,0]
 * Output: 1
 * Explanation:
 * Splitting into two or more chunks will not return the required result.
 * For example, splitting into [4, 3], [2, 1, 0] will result in [3, 4, 0, 1, 2], which isn't sorted.
 * 
 * Example 2:
 * Input: arr = [1,0,2,3,4]
 * Output: 4
 * Explanation:
 * We can split into two chunks, such as [1, 0], [2, 3, 4].
 * However, splitting into [1, 0], [2], [3], [4] is the highest number of chunks possible.
 * 
 * Note:
 * 1. arr will have length in range [1, 10].
 * 2. arr[i] will be a permutation of [0, 1, ..., arr.length - 1].
 * 3. Follow up:
 * 3.1. What if the array is stored on disk, and the memory is limited such that you can only load at most one row of the array into the memory at once?
 * 3.2. What if the array is so large that you can only load up a partial row into the memory at once?
 * 3.3. What if the array is so large that you can only load up a partial column into the memory at once? 
 * 
 */
#include <vector>
using namespace std;

int maxChunkToSorted(vector<int>& arr) {
  int chunks = 0, cur_max = 0;
  for (int i = 0; i < arr.size(); ++i) {
    cur_max = max(cur_max, arr[i]);
    if (cur_max == i) {
      ++chunks;
    }
  }
  return chunks;
}