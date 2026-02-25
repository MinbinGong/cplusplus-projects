/*
 * 1042. Flower Planting With No Adjacent
 *
 * You have N gardens, labelled 1 to N.  In each garden, you want to plant one of 4 types of flowers.
 * 
 * paths[i] = [x, y] describes the existence of a bidirectional path from garden x to garden y.
 * 
 * Also, there is no garden that has more than 3 paths coming into or leaving it.
 * 
 * Your task is to choose a flower type for each garden such that, for any two gardens connected by a path, they have different types of flowers.
 * 
 * Return any such a choice as an array answer, where answer[i] is the type of flower planted in the (i+1)-th garden.  The flower types are denoted 1, 2, 3, or 4.  It is guaranteed an answer exists.
 * 
 * Example 1:
 * Input: N = 3, paths = [[1,2],[2,3],[3,1]]
 * Output: [1,2,3]
 * 
 * Example 2:
 * Input: N = 4, paths = [[1,2],[3,4]]
 * Output: [1,2,1,2]
 * 
 * Example 3:
 * Input: N = 4, paths = [[1,2],[2,3],[3,4],[4,1],[1,3],[2,4]]
 * Output: [1,2,3,4]
 * 
 * Note:
 * 1. 1 <= N <= 10000
 * 2. 0 <= paths.size <= 20000
 * 3. No garden has 4 or more paths coming into or leaving it.
 * 4. It is guaranteed an answer exists.
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> gardenNoAdj(int n, vector<vector<int>>& paths) {
        vector<vector<int>> adj(n);
        for (const auto& p : paths) {
            adj[p[0]-1].push_back(p[1]-1);
            adj[p[1]-1].push_back(p[0]-1);
        }
        
        vector<int> color(n, 0);
        
        for (int i = 0; i < n; i++) {
            int mask = 0;
            for (int neighbor : adj[i]) {
                if (color[neighbor] != 0) {
                    mask |= (1 << (color[neighbor] - 1));
                }
            }
            
            // 找到第一个未使用的花
            for (int f = 1; f <= 4; f++) {
                if (!(mask & (1 << (f - 1)))) {
                    color[i] = f;
                    break;
                }
            }
        }
        
        return color;
    }
};