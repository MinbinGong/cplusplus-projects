/**
 * 1345. Jump Game IV
 * 
 * Given an array of integers arr, you are initially positioned at the first index of the array.
 * In one step you can jump from index i to index:
 * i + 1 where: i + 1 < arr.length.
 * i - 1 where: i - 1 >= 0.
 * j where: arr[i] == arr[j] and i != j.
 * Return the minimum number of steps to reach the last index of the array.
 * 
 * Notice that you can not jump outside of the array at any time.
 * 
 * Example 1:
 * Input: arr = [100,-23,-23,404,100,23,23,23,3,404]
 * Output: 3
 * Explanation: You need three jumps from index 0 --> 4 --> 3 --> 9. Note that index 9 is the last index of the array.
 * 
 * Example 2:
 * Input: arr = [7]
 * Output: 0
 * Explanation: You start at index 0. The last index is 0. You do not need to jump.
 * 
 * Example 3:
 * Input: arr = [7,6,9,6,9,6,9,7]
 * Output: 1
 * Explanation: You start at index 0. The last index is 7. You jump from index 0 --> 7.
 * 
 * Note:
 * 1 <= arr.length <= 5 * 10^4
 * -10^8 <= arr[i] <= 10^8
 * 
 */
#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

class Solution {
public:
    int minJumps(vector<int>& arr) {
        int n = arr.size();
        if (n == 1) return 0;

        // Build graph: value -> list of indices
        unordered_map<int, vector<int>> sameValue;
        for (int i = 0; i < n; ++i) {
            sameValue[arr[i]].push_back(i);
        }

        vector<bool> visited(n, false);
        queue<int> q;
        q.push(0);
        visited[0] = true;
        int steps = 0;

        while (!q.empty()) {
            int size = q.size();
            for (int s = 0; s < size; ++s) {
                int i = q.front();
                q.pop();

                // Check if reached last index
                if (i == n - 1) return steps;

                // Neighbor: i+1
                if (i + 1 < n && !visited[i + 1]) {
                    visited[i + 1] = true;
                    q.push(i + 1);
                }
                // Neighbor: i-1
                if (i - 1 >= 0 && !visited[i - 1]) {
                    visited[i - 1] = true;
                    q.push(i - 1);
                }
                // Neighbors with same value
                if (sameValue.count(arr[i])) {
                    for (int j : sameValue[arr[i]]) {
                        if (!visited[j]) {
                            visited[j] = true;
                            q.push(j);
                        }
                    }
                    // Clear to avoid reprocessing
                    sameValue.erase(arr[i]);
                }
            }
            ++steps;
        }

        return -1; // should never reach here
    }
};