/**
 * 1203. Sort Items by Groups Respecting Dependencies
 * 
 * There are n items each belonging to zero or one of m groups where group[i] is the group that the i-th item belongs to and it's equal to -1 if the i-th item belongs to no group. The items and the groups are zero indexed. A group can have no item belonging to it.
 * 
 * Return a sorted list of the items such that:
 * 
 * The items that belong to the same group are next to each other in the sorted list.
 * There are some relations between these items where beforeItems[i] is a list containing all the items that should come before the i-th item in the sorted array (to the left of the i-th item).
 * Return any solution if there is more than one solution and return an empty list if there is no solution.
 * 
 * Example 1:
 * Input: n = 8, m = 2, group = [-1,-1,1,0,0,1,0,-1], beforeItems = [[],[6],[5],[6],[3,6],[],[],[]]
 * Output: [6,3,4,1,5,2,0,7]
 * 
 * Example 2:
 * Input: n = 8, m = 2, group = [-1,-1,1,0,0,1,0,-1], beforeItems = [[],[6],[5],[6],[3],[],[4],[]]
 * Output: []
 * 
 * Example 3:
 * Input: n = 5, a = 2, b = 11, c = 13
 * Output: 10
 * Explanation: The ugly numbers are 2, 3, 4, 5, 6, 8, 9, 10, 11, 12, 13... The 5th is 10.
 * 
 * Example 4:
 * Input: n = 1000000000, a = 2, b = 217983653, c = 336916467
 * Output: 1999999984
 * Explanation: The minimum absolute difference is 1. List all pairs with difference equal to 1 in ascending order.
 * 
 * Note:
 * 1 <= n, a, b, c <= 10^9
 * 1 <= a * b * c <= 10^18
 */
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<int> sortItems(int n, int m, vector<int>& group, vector<vector<int>>& beforeItems) {
        // Assign new group ids to items with group -1 (each becomes its own group)
        int nextGroupId = m;
        for (int i = 0; i < n; ++i) {
            if (group[i] == -1) {
                group[i] = nextGroupId++;
            }
        }
        int totalGroups = nextGroupId; // m + number of -1 items

        // Build group graph and item graph
        vector<vector<int>> groupAdj(totalGroups);
        vector<int> groupIndeg(totalGroups, 0);
        vector<vector<int>> itemAdj(n);

        for (int i = 0; i < n; ++i) {
            for (int j : beforeItems[i]) {
                // j -> i dependency
                itemAdj[j].push_back(i);
                if (group[j] != group[i]) {
                    // cross‑group dependency
                    groupAdj[group[j]].push_back(group[i]);
                }
            }
        }

        // Compute indegrees for group graph
        for (int u = 0; u < totalGroups; ++u) {
            for (int v : groupAdj[u]) {
                groupIndeg[v]++;
            }
        }

        // Topological sort of groups
        queue<int> q;
        for (int g = 0; g < totalGroups; ++g) {
            if (groupIndeg[g] == 0) q.push(g);
        }
        vector<int> groupOrder;
        while (!q.empty()) {
            int g = q.front(); q.pop();
            groupOrder.push_back(g);
            for (int ng : groupAdj[g]) {
                if (--groupIndeg[ng] == 0) q.push(ng);
            }
        }
        if (groupOrder.size() != totalGroups) return {}; // cycle in group graph

        // Collect items belonging to each group
        vector<vector<int>> itemsInGroup(totalGroups);
        for (int i = 0; i < n; ++i) {
            itemsInGroup[group[i]].push_back(i);
        }

        vector<int> ans;
        // Process groups in the sorted order
        for (int g : groupOrder) {
            const auto& items = itemsInGroup[g];
            if (items.empty()) continue;

            // Compute internal indegrees for items of this group
            unordered_map<int, int> indeg;
            for (int u : items) indeg[u] = 0;
            for (int u : items) {
                for (int v : itemAdj[u]) {
                    if (group[v] == g) {
                        indeg[v]++;
                    }
                }
            }

            // Topological sort inside the group
            queue<int> qitem;
            for (int u : items) {
                if (indeg[u] == 0) qitem.push(u);
            }
            vector<int> sortedItems;
            while (!qitem.empty()) {
                int u = qitem.front(); qitem.pop();
                sortedItems.push_back(u);
                for (int v : itemAdj[u]) {
                    if (group[v] == g) {
                        if (--indeg[v] == 0) qitem.push(v);
                    }
                }
            }
            if (sortedItems.size() != items.size()) return {}; // cycle inside group

            // Append this group's items to the answer
            ans.insert(ans.end(), sortedItems.begin(), sortedItems.end());
        }

        return ans;
    }
};