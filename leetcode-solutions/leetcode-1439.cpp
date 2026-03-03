/**
 * 1439. Find the Kth Smallest Sum of a Matrix With Sorted Rows
 * 
 * You are given an m * n matrix, mat, and an integer k, which has its rows sorted in non-decreasing order.
 * 
 * You are allowed to choose exactly 1 element from each row to form an array. Return the Kth smallest array sum among all possible arrays.
 * 
 * Example 1:
 * 
 * Input: mat = [[1,3,11],[2,4,6]], k = 5
 * Output: 7
 * Explanation: Choosing one element from each row, the first k smallest sum are:
 * [1,2], [1,4], [3,2], [3,4], [1,6]. Where the 5th sum is 7.  
 * 
 * Example 2:
 * 
 * Input: mat = [[1,3,11],[2,4,6]], k = 9
 * Output: 17
 * Explanation: Choosing one element from each row, the first k smallest sum are:
 * [1,2,2], [1,2,3], [1,4,2], [1,4,3], [1,2,6], [1,5,2], [1,5,3]. Where the 9th sum is 17.  
 * 
 * Example 3:
 * 
 * Input: mat = [[1,10,10],[1,4,5],[2,3,6]], k = 7
 * Output: 9
 * Explanation: Choosing one element from each row, the first k smallest sum are:
 * [1,1,2], [1,1,3], [1,4,2], [1,4,3], [1,1,6], [1,5,2], [1,5,3]. Where the 7th sum is 9.  
 * 
 * Note:
 * 1 <= m, n <= 40
 * 1 <= k <= min(200, n ^ m)
 * 1 <= mat[i][j] <= 5000
 * mat[i] is a non decreasing array.
 * 
 */
#include <vector>
#include <deque>
using namespace std;

class Solution {
public:
    int kthSmallest(vector<vector<int>>& mat, int k) {
        int m = mat.size(), n = mat[0].size();
        
        // initial combination: first element of each row
        vector<int> idx(m, 0);
        int sum = 0;
        for (int i = 0; i < m; ++i) sum += mat[i][0];
        
        // min‑heap: stores (sum, indices)
        using State = pair<int, vector<int>>;
        auto cmp = [](const State& a, const State& b) {
            return a.first > b.first;   // smaller sum first
        };
        priority_queue<State, vector<State>, decltype(cmp)> pq(cmp);
        
        set<vector<int>> visited;
        pq.push({sum, idx});
        visited.insert(idx);
        
        // pop k-1 smallest, the next top is the k-th
        for (int t = 1; t < k; ++t) {
            auto [curSum, curIdx] = pq.top();
            pq.pop();
            
            // try to advance one row at a time
            for (int r = 0; r < m; ++r) {
                if (curIdx[r] + 1 < n) {
                    vector<int> nxtIdx = curIdx;
                    nxtIdx[r]++;
                    if (visited.find(nxtIdx) == visited.end()) {
                        int nxtSum = curSum - mat[r][curIdx[r]] + mat[r][nxtIdx[r]];
                        pq.push({nxtSum, nxtIdx});
                        visited.insert(nxtIdx);
                    }
                }
            }
        }
        
        return pq.top().first;
    }
};