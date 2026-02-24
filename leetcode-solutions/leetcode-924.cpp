/*
 * Minimize Malware Spread
 *
 * In a network of nodes, each node i is directly connected to another node j if and only if graph[i][j] = 1.
 *
 * Some nodes initial are initially infected by malware.  Whenever two nodes are directly connected and at least one of those two nodes is infected by malware, both nodes will be infected by malware.  This spread of malware will continue until no more nodes can be infected in this manner.
 *
 * Suppose M(initial) is the final number of nodes infected with malware in the entire network, after the spread of malware stops.
 *
 * We will remove one node from the initial list.  Return the node that if removed, would minimize M(initial).  If multiple nodes could be removed to minimize M(initial), return such a node with the largest index.
 *
 * Note that if a node was removed from the initial list of infected nodes, it may still be infected later as a result of the malware spread.
 *
 * Example 1:
 * Input: graph = [[1,1,0],[1,1,0],[0,0,1]], initial = [0,1]
 * Output: 0
 * Explanation: If we remove node 0, the malware spreads to nodes 1 and 2, which are then infected by malware.
 * If we remove node 1, the malware spreads to node 2, which is then infected by malware.
 * If we remove node 2, neither node 0 nor node 1 are infected.
 * Thus, node 0 is the node that, if removed, would minimize M(initial).
 * 
 * Example 2:
 * Input: graph = [[1,0,0],[0,1,0],[0,0,1]], initial = [0,2]
 * Output: 0
 * Explanation: If we remove node 0, the malware spreads to nodes 1 and 2, which are then infected by malware.
 * If we remove node 2, neither node 0 nor node 1 are infected.
 * Thus, node 0 is the node that, if removed, would minimize M(initial).
 * 
 * Example 3:
 * Input: graph = [[1,1,1],[1,1,1],[1,1,1]], initial = [1,2]
 * Output: 1
 * 
 * Note:
 * 1 < graph.length = graph[0].length <= 300
 * 0 <= graph[i][j] == graph[j][i] <= 1
 * graph[i][i] = 1
 * 1 <= initial.length < graph.length
 * 0 <= initial[i] < graph.length
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    int minMalwareSpread(vector<vector<int>>& graph, vector<int>& initial) {
        int n = graph.size();
        vector<int> comp(n, -1);               // component id for each node
        vector<int> compSize;                   // size of each component
        int compId = 0;

        // Find connected components using BFS
        for (int i = 0; i < n; ++i) {
            if (comp[i] != -1) continue;
            queue<int> q;
            q.push(i);
            comp[i] = compId;
            int size = 0;
            while (!q.empty()) {
                int u = q.front(); q.pop();
                ++size;
                for (int v = 0; v < n; ++v) {
                    if (graph[u][v] == 1 && comp[v] == -1) {
                        comp[v] = compId;
                        q.push(v);
                    }
                }
            }
            compSize.push_back(size);
            ++compId;
        }

        // Count initially infected nodes in each component
        vector<int> initCount(compId, 0);
        for (int node : initial) {
            ++initCount[comp[node]];
        }

        // Evaluate each candidate
        int bestNode = -1;
        int bestSaved = -1;
        for (int node : initial) {
            int c = comp[node];
            int saved = (initCount[c] == 1) ? compSize[c] : 0;
            if (saved > bestSaved || (saved == bestSaved && node < bestNode)) {
                bestSaved = saved;
                bestNode = node;
            }
        }
        return bestNode;
    }
};