/**
 * 1306. Jump Game III
 * 
 * Given an array of non-negative integers arr, you are initially positioned at start index of the array. When you are at index i, you can jump to i + arr[i] or i - arr[i], check if you can reach to any index with value 0.
 * 
 * Notice that you can not jump outside of the array at any time.
 * 
 * Example 1:
 * Input: arr = [4,2,3,0,3,1,2], start = 5
 * Output: true
 * Explanation: 
 * All possible ways to reach at index 3 with value 0 are: 
 * index 5 -> index 4 -> index 1 -> index 3 
 * index 5 -> index 6 -> index 4 -> index 1 -> index 3 
 * 
 * Example 2:
 * Input: arr = [4,2,3,0,3,1,2], start = 0
 * Output: true 
 * Explanation: 
 * One possible way to reach at index 3 with value 0 is: 
 * index 0 -> index 4 -> index 1 -> index 3
 * 
 * No possible way to reach at index 3 with value 0.
 * 
 * Example 3:
 * Input: arr = [3,0,2,1,2], start = 2
 * Output: false
 * Explanation: There is no way to reach at index 1 with value 0.
 * 
 * Note:
 * Each tree has at most 5000 nodes.
 * Each node's value is between [-10^5, 10^5].
 * 
 */
#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    bool canReach(vector<int>& arr, int start) {
        int n = arr.size();
        vector<bool> visited(n, false);
        queue<int> q;
        
        q.push(start);
        visited[start] = true;
        
        while (!q.empty()) {
            int i = q.front();
            q.pop();
            
            // If we reached a zero, success
            if (arr[i] == 0) return true;
            
            // Try jumping to i + arr[i]
            int next = i + arr[i];
            if (next >= 0 && next < n && !visited[next]) {
                visited[next] = true;
                q.push(next);
            }
            
            // Try jumping to i - arr[i]
            next = i - arr[i];
            if (next >= 0 && next < n && !visited[next]) {
                visited[next] = true;
                q.push(next);
            }
        }
        
        return false;
    }
};