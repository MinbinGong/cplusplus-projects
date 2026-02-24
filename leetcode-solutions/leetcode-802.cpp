/*
 * 802. Find Eventual Safe States
 * 
 * In a directed graph, we start at some node and every turn, walk along a directed edge of the graph.  If we reach a node that is terminal (that is, it has no outgoing directed edges), we stop.
 * 
 * Now, say our starting node is eventually safe if and only if we must eventually walk to a terminal node.  More specifically, there exists a natural number K so that for any choice of where to walk, we must have stopped at a terminal node in less than K steps.
 * 
 * Which nodes are eventually safe?  Return them as an array in sorted order.
 * 
 * The directed graph has N nodes with labels 0, 1, ..., N-1, where N is the length of graph.  The graph is given in the following form: graph[i] is a list of labels j such that (i, j) is a directed edge of the graph.
 * 
 * Example:
 * Input: graph = [[1,2],[2,3],[5],[0],[5],[],[]]
 * Output: [2,4,5,6]
 * Explanation: 
 * The given graph is shown above.
 * 
 * Note:
 * graph will have length at most 10000.
 * The number of edges in the graph will not exceed 32000.
 * Each graph[i] will be a sorted list of different integers, chosen within the range [0, graph.length - 1].    
 * 
 */
#include <vector>
#include <functional>
#include <queue>
#include <algorithm>
using namespace std;

class Solution1 {
public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<int> state(n, 0); // 0:未访问, 1:访问中, 2:安全
        vector<int> result;
        
        // DFS 函数：返回节点 node 是否安全
        function<bool(int)> dfs = [&](int node) -> bool {
            if (state[node] > 0) // 已经知道结果
                return state[node] == 2;
            
            state[node] = 1; // 标记为访问中
            
            for (int neighbor : graph[node]) {
                if (state[neighbor] == 1) // 遇到当前路径上的节点，说明有环
                    return false;
                if (state[neighbor] == 0 && !dfs(neighbor)) // 邻居不安全
                    return false;
            }
            
            state[node] = 2; // 所有邻居都安全，当前节点也安全
            return true;
        };
        
        for (int i = 0; i < n; i++) {
            if (dfs(i))
                result.push_back(i);
        }
        
        return result;
    }
};

class Solution2 {
public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<vector<int>> reverseGraph(n); // 反图：记录指向某个节点的所有节点
        vector<int> outdegree(n, 0);         // 出度
        queue<int> q;
        vector<int> result;
        
        // 构建反图并统计出度
        for (int i = 0; i < n; i++) {
            outdegree[i] = graph[i].size();
            if (outdegree[i] == 0)           // 终端节点入队
                q.push(i);
            for (int neighbor : graph[i]) {
                reverseGraph[neighbor].push_back(i); // neighbor -> i 的反向边
            }
        }
        
        // 逆向 BFS
        while (!q.empty()) {
            int curr = q.front();
            q.pop();
            result.push_back(curr);
            
            // 遍历所有指向 curr 的节点（即原图中 curr 的前驱）
            for (int prev : reverseGraph[curr]) {
                outdegree[prev]--;            // prev 的一条出路通向安全节点
                if (outdegree[prev] == 0) {   // prev 所有出路都通向安全节点
                    q.push(prev);
                }
            }
        }
        
        sort(result.begin(), result.end());   // 题目要求升序返回
        return result;
    }
};