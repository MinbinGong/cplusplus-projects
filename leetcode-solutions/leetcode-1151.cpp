/**
 * 1151. Minimum Swaps to Group All 1's Together
 * Medium
 * 
 * (This problem is an interactive problem.)
 * 
 * Given a binary array data, return the minimum number of swaps required to group all 1’s present in the array together in any place in the array.
 * 
 * Example 1:
 * Input: data = [1,0,1,0,1]
 * Output: 1
 * Explanation: 
 * There are 3 ways to group all 1's together:
 * [1,1,1,0,0] using 1 swap.
 * [0,1,1,1,0] using 2 swaps (using the circular property of the array).
 * [0,0,1,1,1] using 1 swap.
 * The minimum is 1.
 * 
 * Example 2:
 * Input: data = [0,0,0,1,0]
 * Output: 0
 * Explanation: 
 * Since there is only one 1 in the array, no swaps needed.
 * 
 * Note:
 * 1 <= data.length <= 10^5
 * 0 <= data[i] <= 1
 * 
 */
#include <vector>
#include <numeric>
using namespace std;

class Solution {
public:
    int minSwaps(vector<int>& data) {
        int totalOnes = accumulate(data.begin(), data.end(), 0);
        if (totalOnes <= 1) return 0;
        
        int left = 0, curOnes = 0, maxOnes = 0;
        for (int right = 0; right < data.size(); ++right) {
            curOnes += data[right];
            if (right - left + 1 > totalOnes) {
                curOnes -= data[left++];
            }
            if (right - left + 1 == totalOnes) {
                maxOnes = max(maxOnes, curOnes);
            }
        }
        return totalOnes - maxOnes;
    }
};