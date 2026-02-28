/**
 * 1213. Intersection of Three Sorted Arrays
 *
 * Given three integer arrays arr1, arr2 and arr3 sorted in strictly increasing order, return a sorted array of only the integers that appeared in all three arrays.
 *
 * Example 1:
 *
 * Input: arr1 = [1,2,3,4,5], arr2 = [1,2,5,7,9], arr3 = [1,3,4,5,8]
 * Output: [1,5]
 * Explanation: Only 1 and 5 appeared in the three arrays.
 *
 * Constraints:
 * 1 <= arr1.length, arr2.length, arr3.length <= 1000
 * 1 <= arr1[i], arr2[i], arr3[i] <= 2000
 *
 */
#include <vector>

class Solution {
public:
    std::vector<int> arraysIntersection(std::vector<int>& arr1, std::vector<int>& arr2, std::vector<int>& arr3) {
        std::vector<int> result;
        int i = 0, j = 0, k = 0;
        int n1 = arr1.size(), n2 = arr2.size(), n3 = arr3.size();
        
        while (i < n1 && j < n2 && k < n3) {
            if (arr1[i] == arr2[j] && arr2[j] == arr3[k]) {
                result.push_back(arr1[i]);
                i++;
                j++;
                k++;
            } else {
                // 找到三个元素中的最小值，并将对应的指针向前移动
                int minVal = std::min(arr1[i], std::min(arr2[j], arr3[k]));
                if (arr1[i] == minVal) i++;
                if (arr2[j] == minVal) j++;
                if (arr3[k] == minVal) k++;
            }
        }
        
        return result;
    }
};