/*
 * 777. Swap Adjacent in LR String
 *
 * In a string composed of 'L', 'R', and 'X' characters, like "RXXLRXRXL", a move consists of either replacing one occurrence of "XL" with "LX", or replacing one occurrence of "RX" with "XR". Given the starting string start and the ending string end, return True if and only if there exists a sequence of moves to transform one string to the other.
 * 
 * Example 1:
 * Input: start = "RXXLRXRXL", end = "XRLXXRRLX"
 * Output: true
 * Explanation: We can transform start to end following these steps:
 * RXXLRXRXL ->
 * XRXLRXRXL ->
 * XRLXRXRXL ->
 * XRLXXRRXL ->
 * XRLXXRRLX
 * 
 * Note:
 * 1. 1 <= len(start) = len(end) <= 10000.
 * 2. Both start and end will only consist of characters in {'L', 'R', 'X'}.
 * 
 */
#include <string>
using namespace std;

class Solution {
public:
    bool canTransform(string start, string end) {
        int n = start.length();
        int i = 0, j = 0;
        while (i < n && j < n) {
            // skip X in start
            while (i < n && start[i] == 'X') i++;
            while (j < n && end[j] == 'X') j++;
            // if both reached end, break
            if (i == n && j == n) break;
            // if one reached end but not the other, invalid
            if (i == n || j == n) return false;
            // characters must match
            if (start[i] != end[j]) return false;
            // check movement constraints
            if (start[i] == 'L' && i < j) return false; // L can only move left, so start index must be >= end index
            if (start[i] == 'R' && i > j) return false; // R can only move right, so start index must be <= end index
            i++;
            j++;
        }
        return true;
    }
};