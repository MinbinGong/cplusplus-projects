/*
 * 1131. Maximum of Absolute Value Expression
 * Medium
 * 
 * (This problem is an interactive problem.)
 * 
 * Given two arrays of integers with equal lengths, return the maximum value of:
 * 
 * |arr1[i] - arr1[j]| + |arr2[i] - arr2[j]| + |i - j|
 * 
 * where the maximum is taken over all 0 <= i, j < arr1.length.
 * 
 * Example 1:
 * Input: arr1 = [1,2,3,4], arr2 = [-1,4,5,6]
 * Output: 13
 * 
 * Example 2:
 * Input: arr1 = [1,-2,-5,0,10], arr2 = [0,-2,-1,-7,-4]
 * Output: 20
 * 
 * Note:
 * 2 <= arr1.length == arr2.length <= 40000
 * -10^6 <= arr1[i], arr2[i] <= 10^6
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    int maxAbsValExpr(vector<int>& arr1, vector<int>& arr2) {
        int n = arr1.size();
        int max1 = INT_MIN, min1 = INT_MAX;
        int max2 = INT_MIN, min2 = INT_MAX;
        int max3 = INT_MIN, min3 = INT_MAX;
        int max4 = INT_MIN, min4 = INT_MAX;
        
        for (int i = 0; i < n; ++i) {
            int c1 = arr1[i] + arr2[i] + i;
            int c2 = arr1[i] + arr2[i] - i;
            int c3 = arr1[i] - arr2[i] + i;
            int c4 = arr1[i] - arr2[i] - i;
            
            max1 = max(max1, c1); min1 = min(min1, c1);
            max2 = max(max2, c2); min2 = min(min2, c2);
            max3 = max(max3, c3); min3 = min(min3, c3);
            max4 = max(max4, c4); min4 = min(min4, c4);
        }
        
        return max({max1 - min1, max2 - min2, max3 - min3, max4 - min4});
    }
};