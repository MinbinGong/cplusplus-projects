/*
 * 1202. Smallest String With Swaps
 *
 * You are given a string s, and an array of pairs of indices in the string pairs where pairs[i] = [a, b] indicates 2 indices(0-indexed) of the string.
 * 
 * You can swap the characters at any pair of indices in the given pairs any number of times.
 * 
 * Return the lexicographically smallest string that s can be changed to after using the swaps.
 * 
 * Example 1:
 * Input: s = "dcab", pairs = [[0,3],[1,2]]
 * Output: "bacd"
 * Explantion: 
 * Swap s[0] and s[3], s = "bcad"
 * Swap s[1] and s[2], s = "bacd"
 * 
 * Example 2:
 * Input: s = "dcab", pairs = [[0,3],[1,2],[0,2]]
 * Output: "abcd"
 * Explantion: 
 * Swap s[0] and s[3], s = "bcad"
 * Swap s[0] and s[2], s = "acbd"
 * Swap s[1] and s[2], s = "abcd"
 * 
 * Example 3:
 * Input: s = "cba", pairs = [[0,1],[1,2]]
 * Output: "abc"
 * Explantion: 
 * Swap s[0] and s[1], s = "bca"
 * Swap s[1] and s[2], s = "bac"
 * Swap s[0] and s[1], s = "abc"
 * 
 * Note:
 * 1 <= s.length <= 10^5
 * 0 <= pairs.length <= 10^5
 * 0 <= pairs[i][0], pairs[i][1] < s.length
 * s only contains lower case English letters.
 * 
 */
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
public:
    string smallestStringWithSwaps(string s, vector<vector<int>>& pairs) {
        int n = s.length();
        vector<int> parent(n);
        vector<int> size(n, 1);
        
        // Initialize DSU: each node is its own parent
        for (int i = 0; i < n; ++i) parent[i] = i;
        
        // Find with path compression
        function<int(int)> find = [&](int x) {
            if (parent[x] != x) parent[x] = find(parent[x]);
            return parent[x];
        };
        
        // Union by size
        auto unite = [&](int x, int y) {
            int rx = find(x), ry = find(y);
            if (rx == ry) return;
            if (size[rx] < size[ry]) swap(rx, ry);
            parent[ry] = rx;
            size[rx] += size[ry];
        };
        
        // Union all given pairs
        for (auto& p : pairs) {
            unite(p[0], p[1]);
        }
        
        // Group indices by their root
        unordered_map<int, vector<int>> components;
        for (int i = 0; i < n; ++i) {
            components[find(i)].push_back(i);
        }
        
        // For each component, sort indices and corresponding characters
        for (auto& [root, indices] : components) {
            // Sort indices to assign characters in increasing index order
            sort(indices.begin(), indices.end());
            
            // Collect characters from these indices
            vector<char> chars;
            for (int idx : indices) chars.push_back(s[idx]);
            
            // Sort characters to get the smallest possible arrangement
            sort(chars.begin(), chars.end());
            
            // Place sorted characters back into the string
            for (int k = 0; k < indices.size(); ++k) {
                s[indices[k]] = chars[k];
            }
        }
        
        return s;
    }
};