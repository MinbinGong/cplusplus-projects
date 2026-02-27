/*
 * 1089. Duplicate Zeros
 *
 * Given a fixed length array arr of integers, duplicate each occurrence of zero, shifting the remaining elements to the right.
 * Note that elements beyond the length of the original array are not written.
 * Do the above modifications to the input array in place, do not return anything from your function.
 * 
 * Example 1:
 * Input: [1,0,2,3,0,4,5,0]
 * Output: null
 * Explanation: After calling your function, the input array is modified to: [1,0,0,2,3,0,0,4]
 * 
 * Example 2:
 * Input: [1,2,3]
 * Output: null
 * Explanation: After calling your function, the input array is modified to: [1,2,3]
 * 
 * Note:
 * 1 <= arr.length <= 10000
 * 0 <= arr[i] <= 9
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    void duplicateZeros(vector<int>& arr) {
        int n = arr.size();
        int zeros = 0;
        for (int num : arr) {
            if (num == 0) zeros++;
        }
        
        int i = n - 1;               // last index of original array
        int j = n + zeros - 1;        // last index after expansion (may be >= n)
        
        while (i >= 0) {
            if (arr[i] == 0) {
                // duplicate zero
                if (j < n) arr[j] = 0;
                j--;
                if (j < n) arr[j] = 0;
                j--;
            } else {
                if (j < n) arr[j] = arr[i];
                j--;
            }
            i--;
        }
    }
};