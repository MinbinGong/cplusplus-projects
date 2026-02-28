/**
 * 1207. Unique Number of Occurrences
 * 
 * Given an array of integers arr, write a function that returns true if and only if the number of occurrences of each value in the array is unique.
 * 
 * Example 1:
 * Input: arr = [1,2,2,1,1,3]
 * Output: true
 * Explanation: The value 1 has 3 occurrences, 2 has 2 and 3 has 1. No two values have the same number of occurrences.
 * 
 * Example 2:
 * Input: arr = [1,2]
 * Output: false
 * 
 * Example 3:
 * Input: arr = [-3,0,1,-3,1,1,1,-3,10,0]
 * Output: true
 * 
 * Note:
 * 1 <= arr.length <= 1000
 * -1000 <= arr[i] <= 1000
 * 
 */
#include <vector>
#include <unordered_map>
#include <unordered_set>

class Solution {
public:
    bool uniqueOccurrences(std::vector<int>& arr) {
        std::unordered_map<int, int> countMap;
        for (int num : arr) {
            countMap[num]++;
        }
        
        std::unordered_set<int> occurrencesSet;
        for (const auto& pair : countMap) {
            if (occurrencesSet.count(pair.second) > 0) {
                return false;
            }
            occurrencesSet.insert(pair.second);
        }
        
        return true;
    }
};