#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Solution {
public:
    string findSmallestRegion(vector<vector<string>>& regions, string region1, string region2) {
        unordered_map<string, string> parent;
        // Build parent map: for each region in the list (except the first), its parent is the first region.
        for (const auto& list : regions) {
            for (size_t i = 1; i < list.size(); ++i) {
                parent[list[i]] = list[0];
            }
        }

        // Collect all ancestors of region1.
        unordered_set<string> ancestors;
        string cur = region1;
        while (true) {
            ancestors.insert(cur);
            if (parent.find(cur) == parent.end()) break;
            cur = parent[cur];
        }

        // Climb region2 until we find a common ancestor.
        cur = region2;
        while (true) {
            if (ancestors.count(cur)) return cur;
            if (parent.find(cur) == parent.end()) break;
            cur = parent[cur];
        }

        return ""; // should never reach here given valid input
    }
};