/**
 * 975. Odd Even Jump
 *
 * You are given an integer array arr. From some starting index, you can make a series of jumps. The (1st, 3rd, 5th, ...) jumps in the series are called odd-numbered jumps, and the (2nd, 4th, 6th, ...) jumps in the series are called even-numbered jumps. Note that the jumps are numbered, not the indices.
 *
 * You may jump forward from index i to index j (with i < j) in the following way:
 *
 * During odd-numbered jumps (i.e., jumps 1, 3, 5, ...), you jump to the index j such that arr[i] <= arr[j] and arr[j] is the smallest possible value. If there are multiple such indices j, you can only jump to the smallest such index j.
 * During even-numbered jumps (i.e., jumps 2, 4, 6, ...), you jump to the index j such that arr[i] >= arr[j] and arr[j] is the largest possible value. If there are multiple such indices j, you can only jump to the smallest such index j.
 * 
 * Example 1:
 *
 * Input: arr = [10,13,12,14,15]
 * Output: 2
 * Explanation: 
 * From starting index i = 0, we can make our 1st jump to i = 2 (since arr[2] is the smallest among arr[1], arr[2], arr[3], arr[4] that is greater or equal to arr[0]), then we cannot jump any more.
 * From starting index i = 1 and i = 2, we can make our 1st jump to i = 3, then we cannot jump any more.
 * From starting index i = 3, we can make our 1st jump to i = 4, so we have reached the end.
 * From starting index i = 4, we have reached the end already.
 * In total, there are 2 different starting indices i = 3 and i = 4 where we can reach the end with some number of jumps.
 * 
 * Example 2:
 *
 * Input: arr = [2,3,1,1,4]
 * Output: 3
 * Explanation: 
 * From starting index i = 0, we make jumps to i = 1, i = 2, i = 3:
 * During our 1st jump (odd-numbered), we first jump to i = 1 because arr[1] is the smallest value in [arr[1], arr[2], arr[3], arr[4]] that is greater than or equal to arr[0].
 * During our 2nd jump (even-numbered), we jump from i = 1 to i = 2 because arr[2] is the largest value in [arr[2], arr[3], arr[4]] that is less than or equal to arr[1]. arr[3] is also the largest value, but 2 is a smaller index, so we can only jump to i = 2 and not i = 3.
 * 
 * Example 3:
 *
 * Input: arr = [5,1,3,4,2]
 * Output: 3
 * Explanation: 
 * We can reach the end from starting indices 1, 2, and 4.
 * 
 * Note:
 *
 * 1 <= arr.length <= 2 * 104
 * 0 <= arr[i] < 105
 */
#include <vector>
#include <map>
using namespace std;

class Solution {
public:
    int oddEvenJumps(vector<int>& A) {
        int n = A.size();
        if (n == 0) return 0;
        vector<bool> odd(n, false), even(n, false);
        odd[n-1] = even[n-1] = true;
        map<int, int> valToIndex; // 值到索引的映射
        valToIndex[A[n-1]] = n-1;
        
        int res = 1; // 最后一个位置是有效起点
        for (int i = n-2; i >= 0; --i) {
            int val = A[i];
            // 奇数次跳跃：找大于等于val的最小值
            auto it = valToIndex.lower_bound(val);
            if (it != valToIndex.end()) {
                odd[i] = even[it->second];
            }
            // 偶数次跳跃：找小于等于val的最大值
            it = valToIndex.upper_bound(val);
            if (it != valToIndex.begin()) {
                --it;
                even[i] = odd[it->second];
            }
            valToIndex[val] = i; // 插入当前值（覆盖重复值以确保最小索引）
            if (odd[i]) res++;
        }
        return res;
    }
};