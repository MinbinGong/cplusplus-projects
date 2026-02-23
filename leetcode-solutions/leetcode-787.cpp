/*
 * 787. Cheapest Flights Within K Stops
 *
 * There are n cities connected by m flights. Each fight starts from city u and arrives at v with a price w.
 * 
 * Now given all the cities and flights, together with starting city src and the destination dst, your task is to find the cheapest price from src to dst with up to k stops. If there is no such route, output -1.
 * 
 * Example 1:
 * Input: 
 * n = 3, edges = [[0,1,100],[1,2,100],[0,2,500]]
 * src = 0, dst = 2, k = 1
 * Output: 200
 * Explanation: 
 * The graph looks like this:
 * 
 * The cheapest price from city 0 to city 2 with at most 1 stop costs 200, as marked red in the picture.
 * 
 * Example 2:
 * Input: 
 * n = 3, edges = [[0,1,100],[1,2,100],[0,2,500]]
 * src = 0, dst = 2, k = 0
 * Output: 500
 * Explanation: 
 * The graph looks like this:
 * 
 * The cheapest price from city 0 to city 2 with at most 0 stop costs 500, as marked blue in the picture.
 * 
 * Note:
 * 1. The number of nodes n will be in range [1, 100], with nodes labeled from 0 to n - 1.
 * 2. The size of flights will be in range [0, n * (n - 1) / 2].
 * 3. The format of each flight will be (src, dst, price).
 * 4. The price of each flight will be in the range [1, 10000].
 * 5. k is in the range of [0, n - 1].
 * 6. There will not be any duplicated flights or self cycles.
 * 
 */
#include <vector>
#include <climits>

using namespace std;

class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int K) {
        const int INF = 1e9;
        vector<int> dist(n, INF);
        dist[src] = 0;

        // Relax up to K+1 times (since K stops means at most K+1 edges)
        for (int i = 0; i <= K; ++i) {
            vector<int> temp = dist; // start from previous iteration's distances
            for (auto& f : flights) {
                int u = f[0], v = f[1], w = f[2];
                if (dist[u] != INF && dist[u] + w < temp[v]) {
                    temp[v] = dist[u] + w;
                }
            }
            dist = temp;
        }

        return dist[dst] == INF ? -1 : dist[dst];
    }
};