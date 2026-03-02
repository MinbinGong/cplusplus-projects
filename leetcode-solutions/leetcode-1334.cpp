/*
 * 1334. Find the City With the Smallest Number of Neighbors at a Threshold Distance
 *
 * There are n cities numbered from 0 to n-1. Given the array edges where edges[i] = [fromi, toi, weighti] represents a bidirectional and weighted edge between cities fromi and toi, and given the integer distanceThreshold.
 *
 * Return the city with the smallest number of cities that are reachable through some path and whose distance is at most distanceThreshold, If there are multiple such cities, return the city with the greatest number.
 *
 * Notice that the distance of a path connecting cities i and j is equal to the sum of the edges' weights along that path.
 *
 * Example 1:
 * Input: n = 4, edges = [[0,1,3],[1,2,1],[1,3,4],[2,3,1]], distanceThreshold = 4
 * Output: 3
 * Explanation: The figure above describes the graph. 
 * The neighboring cities at a distanceThreshold = 4 for each city are:
 * 
 * Example 2:
 * Input: n = 5, edges = [[0,1,2],[0,4,8],[1,2,3],[1,4,2],[2,3,1],[3,4,1]], distanceThreshold = 2
 * Output: 0
 * Explanation: The figure above describes the graph. 
 * The neighboring cities at a distanceThreshold = 2 for each city are:
 * 
 * Note:
 * 1 <= n <= 100
 * 1 <= edges.length <= n * (n - 1) / 2
 * edges[i].length == 3
 * 0 <= fromi < toi < n
 * 1 <= weighti, distanceThreshold <= 10^4
 * All pairs (fromi, toi) are distinct.
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
        const int INF = 1e9;
        vector<vector<int>> dist(n, vector<int>(n, INF));
        
        // Initialize distances
        for (int i = 0; i < n; ++i) dist[i][i] = 0;
        for (auto& e : edges) {
            int u = e[0], v = e[1], w = e[2];
            dist[u][v] = w;
            dist[v][u] = w;
        }
        
        // Floyd-Warshall
        for (int k = 0; k < n; ++k) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (dist[i][k] < INF && dist[k][j] < INF) {
                        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                    }
                }
            }
        }
        
        int bestCity = -1;
        int minCount = n; // can't exceed n-1
        
        for (int i = 0; i < n; ++i) {
            int cnt = 0;
            for (int j = 0; j < n; ++j) {
                if (j != i && dist[i][j] <= distanceThreshold) {
                    cnt++;
                }
            }
            if (cnt < minCount) {
                minCount = cnt;
                bestCity = i;
            } else if (cnt == minCount) {
                if (i > bestCity) bestCity = i;
            }
        }
        
        return bestCity;
    }
};