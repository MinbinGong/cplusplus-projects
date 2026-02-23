/*
 * 797. All Paths From Source to Target
 *
 * Given a directed, acyclic graph of N nodes. Find all possible paths from node 0 to node N-1, and return them in any order.
 * 
 * The graph is given as follows:  the nodes are 0, 1, ..., graph.length - 1.  graph[i] is a list of all nodes j for which the edge (i, j) exists.
 * 
 * Example:
 * Input: [[1,2], [3], [3], []] 
 * Output: [[0,1,3],[0,2,3]] 
 * Explanation: The graph looks like this:
 * 0--->1
 * |    |
 * v    v
 * 2--->3
 * There are two paths: 0 -> 1 -> 3 and 0 -> 2 -> 3.
 * 
 * Note:
 * 1. The number of nodes in the graph will be in the range [2, 15].
 * 2. The graph[i] list will not contain duplicates.
 * 3. The graph[i] list will not contain the node i.
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
        vector<vector<int>> result;
        vector<int> path;
        path.push_back(0); // start from node 0
        dfs(graph, 0, path, result);
        return result;
    }

private:
    void dfs(vector<vector<int>>& graph, int node, vector<int>& path, vector<vector<int>>& result) {
        if (node == graph.size() - 1) { // reached target
            result.push_back(path);
            return;
        }
        for (int next : graph[node]) {
            path.push_back(next);
            dfs(graph, next, path, result);
            path.pop_back(); // backtrack
        }
    }
};