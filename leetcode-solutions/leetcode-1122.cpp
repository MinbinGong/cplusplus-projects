/**
 * Relative Sort Array
 * 
 * Given two arrays arr1 and arr2, the elements of arr2 are distinct, and all elements in arr2 are also in arr1.
 * 
 * Sort the elements of arr1 such that the relative ordering of items in arr1 are the same as in arr2.
 * Elements that don't appear in arr2 should be placed at the end of arr1 in ascending order.
 * 
 * 1 <= arr1.length, arr2.length <= 1000
 * 0 <= arr1[i], arr2[i] <= 1000
 * All the elements of arr2 are distinct.
 * Each arr2[i] is in arr1.
 */
#include <vector>
using namespace std;

class Solution1 {
public:
    vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2) {
        // Counting sort approach because values are in range [0, 1000]
        int count[1001] = {0};
        
        // Count frequency of each number in arr1
        for (int num : arr1) {
            count[num]++;
        }
        
        vector<int> result;
        
        // Place elements in order of arr2
        for (int num : arr2) {
            while (count[num]-- > 0) {
                result.push_back(num);
            }
        }
        
        // Place remaining elements in ascending order
        for (int i = 0; i <= 1000; i++) {
            while (count[i]-- > 0) {
                result.push_back(i);
            }
        }
        
        return result;
    }
};