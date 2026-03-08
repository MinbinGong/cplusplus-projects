/*
 * 1640. Check Array Formation Through Concatenation
 *
 * You are given an array of distinct integers arr and an array of integer arrays pieces, where the integers in pieces are distinct. Your goal is to form arr by concatenating the arrays in pieces in any order. However, you are not allowed to reorder the integers in each array pieces[i].
 *
 * Return true if it is possible to form the array arr from pieces. Otherwise, return false.
 * 
 * Example 1:
 * Input: arr = [15,88], pieces = [[88],[15]]
 * Output: true
 * Explanation: Concatenate [15] then [88]
 * 
 * Example 2:
 * Input: arr = [49,18,16], pieces = [[16,18,49]]
 * Output: false
 * Explanation: Even though the numbers match, we cannot reorder pieces[0].
 * 
 * Constraints:
 * 1 <= pieces.length <= arr.length <= 100
 * sum(pieces[i].length) == arr.length
 * 1 <= pieces[i].length <= arr.length
 * 1 <= arr[i], pieces[i][j] <= 100
 * The integers in arr are distinct.
 * The integers in pieces are distinct (i.e., If we flatten pieces in a 1D array, all the integers in this array are distinct).
 * 
 */
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    bool canFormArray(vector<int>& arr, vector<vector<int>>& pieces) {
        // Map first element of each piece to the piece itself
        unordered_map<int, vector<int>> firstToPiece;
        for (auto& piece : pieces) {
            firstToPiece[piece[0]] = piece;
        }

        int i = 0, n = arr.size();
        while (i < n) {
            // If current element is not the start of any piece, fail
            if (firstToPiece.find(arr[i]) == firstToPiece.end()) {
                return false;
            }

            // Get the piece that should start here
            vector<int>& piece = firstToPiece[arr[i]];
            // Verify that the piece matches arr sequentially
            for (int num : piece) {
                if (i >= n || arr[i] != num) {
                    return false;
                }
                i++;
            }
        }
        return true;
    }
};