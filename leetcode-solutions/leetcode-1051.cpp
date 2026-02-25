/*
 * 1051. Height Checker
 *
 * Students are asked to stand in non-decreasing order of heights for an annual photo.
 * 
 * Return the minimum number of students that must move in order for all students to be standing in non-decreasing order of height.
 * 
 * Example 1:
 * Input: [1,1,4,2,1,3]
 * Output: 3
 * Explanation: 
 * Students with heights 4, 3 and the last 1 are not standing in the right positions.
 * 
 * Example 2:
 * Input: [2,1,2,1,1,2,2,1]
 * Output: 4
 * Explanation: 
 * Students with heights 2, 1, 2, 1, 1, 2, 2, 1 are not standing in the right positions.
 * 
 * Note:
 * 1. 1 <= heights.length <= 100
 * 2. 1 <= heights[i] <= 100
 * 
 */
#include <vector>
#include <algorithm>
#include <array>

using namespace std;

class Solution1 {
public:
    int heightChecker(vector<int>& heights) {
        vector<int> expected = heights;
        sort(expected.begin(), expected.end());
        
        int count = 0;
        for (size_t i = 0; i < heights.size(); ++i) {
            if (heights[i] != expected[i]) {
                ++count;
            }
        }
        return count;
    }
};

class Solution2 {
public:
    int heightChecker(vector<int>& heights) {
        array<int, 101> freq = {0};   // heights range 1..100
        for (int h : heights) {
            ++freq[h];
        }
        
        int count = 0;
        int expectedHeight = 1;        // start from the smallest height
        for (int h : heights) {
            // find the next expected height that still has remaining count
            while (freq[expectedHeight] == 0) {
                ++expectedHeight;
            }
            // if current height doesn't match, increment count
            if (h != expectedHeight) {
                ++count;
            }
            // consume one occurrence of the expected height
            --freq[expectedHeight];
        }
        return count;
    }
};