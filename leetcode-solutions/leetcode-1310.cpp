/**
 * 1310. XOR Queries of a Subarray
 * 
 * Given the array arr of positive integers and the array queries where queries[i] = [Li, Ri], for each query i compute the XOR of elements from Li to Ri (that is, arr[Li] xor arr[Li+1] xor ... xor arr[Ri] ). Return an array containing the result for the given queries.
 * 
 * Example 1:
 * Input: arr = [1,3,4,8], queries = [[0,1],[1,2],[0,3],[3,3]]
 * Output: [2,7,14,8] 
 * Explanation: 
 * The binary representation of the elements in the array are:
 * 1 = 0001 
 * 3 = 0011 
 * 4 = 0100 
 * 8 = 1000 
 * The XOR values for queries are:
 * [0,1] = 1 xor 3 = 2 
 * [1,2] = 3 xor 4 = 7 
 * [0,3] = 1 xor 3 xor 4 xor 8 = 14 
 * [3,3] = 8
 * 
 * Example 2:
 * Input: arr = [4,8,2,10], queries = [[2,3],[1,3],[0,0],[0,3]]
 * Output: [8,0,4,4]
 * Explanation: 
 * The binary representation of the elements in the array are:
 * 4 = 0100 
 * 8 = 1000 
 * 2 = 0010 
 * 10 = 1010 
 * The XOR values for queries are:
 * [2,3] = 2 xor 10 = 8 
 * [1,3] = 8 xor 2 xor 10 = 0 
 * [0,0] = 4 
 * [0,3] = 4 xor 8 xor 2 xor 10 = 4
 * 
 * Note:
 * 1 <= arr.length <= 3 * 10^4
 * 1 <= arr[i] <= 10^9
 * 1 <= queries.length <= 3 * 10^4
 * queries[i].length == 2
 * 0 <= queries[i][0] <= queries[i][1] < arr.length
 */
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> xorQueries(vector<int>& arr, vector<vector<int>>& queries) {
        int n = arr.size();
        vector<int> prefix(n + 1, 0); // prefix[i] 表示 arr[0..i-1] 的异或值
        for (int i = 0; i < n; ++i) {
            prefix[i + 1] = prefix[i] ^ arr[i];
        }
        
        vector<int> ans;
        for (auto& q : queries) {
            int l = q[0], r = q[1];
            // 区间 [l, r] 的异或 = prefix[r+1] ^ prefix[l]
            ans.push_back(prefix[r + 1] ^ prefix[l]);
        }
        return ans;
    }
};