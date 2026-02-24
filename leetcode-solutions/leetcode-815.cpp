/*
 * 815. Bus Routes
 * 
 * You are given an array routes representing bus routes where routes[i] is a bus route that the ith bus repeats forever.
 * 
 * For example, if routes[0] = [1, 5, 7], this means that the 0th bus travels in the sequence 1 -> 5 -> 7 -> 1 -> 5 -> 7 -> 1 -> ... forever.
 * 
 * You will start at the bus stop source (You are not on any bus initially), and you want to go to the bus stop target. You can travel between bus stops by buses only.
 * 
 * Return the least number of buses you must take to travel from source to target. Return -1 if it is not possible.
 * 
 * Example:
 * Input: routes = [[1,2,7],[3,6,7]], source = 1, target = 6
 * Output: 2
 * Explanation: 
 * The best strategy is take the first bus to the bus stop 7, then take the second bus to the bus stop 6.
 * 
 * Note:
 * 1 <= routes.length <= 500.
 * 1 <= routes[i].length <= 105.
 * All the values of routes[i] are unique.
 * sum(routes[i].length) <= 105.
 * 0 <= routes[i][j] < 106.
 * 0 <= source, target < 106.
 * 
 */
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
using namespace std;

class Solution {
public:
    int numBusesToDestination(vector<vector<int>>& routes, int S, int T) {
        if (S == T) return 0;

        int n = routes.size();
        // 映射：每个站点 -> 经过它的公交线路
        unordered_map<int, vector<int>> stationToBuses;
        for (int i = 0; i < n; ++i) {
            for (int station : routes[i]) {
                stationToBuses[station].push_back(i);
            }
        }

        queue<int> q;
        unordered_set<int> visitedStations;
        vector<bool> visitedBuses(n, false);

        q.push(S);
        visitedStations.insert(S);
        int steps = 0;

        while (!q.empty()) {
            int levelSize = q.size();
            for (int i = 0; i < levelSize; ++i) {
                int cur = q.front();
                q.pop();

                if (cur == T) return steps;  // 到达终点，返回当前乘车数

                // 所有经过当前站点的公交线路
                for (int bus : stationToBuses[cur]) {
                    if (visitedBuses[bus]) continue;
                    visitedBuses[bus] = true;

                    // 乘坐该公交，将其所有未访问站点加入队列
                    for (int station : routes[bus]) {
                        if (!visitedStations.count(station)) {
                            visitedStations.insert(station);
                            q.push(station);
                        }
                    }
                }
            }
            ++steps;  // 完成一层，乘车数加1
        }

        return -1;  // 无法到达
    }
};