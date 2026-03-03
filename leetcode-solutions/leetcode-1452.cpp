/*
 * 1452. People Whose List of Favorite Companies Is Not a Subset of Another List
 *
 * Given the array favoriteCompanies where favoriteCompanies[i] is the list of favorites companies for the ith person (indexed from 0).
 * 
 * Return the indices of people whose list of favorite companies is not a subset of any other list of favorites companies. You must return the indices in increasing order.
 * 
 * Example 1:
 * 
 * Input: favoriteCompanies = [["leetcode","google","facebook"],["google","microsoft"],["google","facebook"],["google"],["amazon"]]
 * Output: [0,1,4] 
 * Explanation: 
 * Person with index=2 has favoriteCompanies[2]=["google","facebook"] which is a subset of favoriteCompanies[0]=["leetcode","google","facebook"] corresponding to the person with index 0. 
 * Person with index=3 has favoriteCompanies[3]=["google"] which is a subset of favoriteCompanies[0]=["leetcode","google","facebook"] and favoriteCompanies[1]=["google","microsoft"]. 
 * Other lists of favorite companies are not a subset of another list, therefore, the answer is [0,1,4].
 * 
 * Example 2:
 * 
 * Input: favoriteCompanies = [["leetcode","google","facebook"],["leetcode","amazon"],["facebook","google"]]
 * Output: [0,1] 
 * Explanation: Person with index=2 has favoriteCompanies[2]=["facebook","google"] which is a subset of favoriteCompanies[0]=["leetcode","google","facebook"], therefore, the answer is [0,1].
 * 
 * Example 3:
 * 
 * Input: favoriteCompanies = [["leetcode"],["google"],["facebook"],["amazon"]]
 * Output: [0,1,2,3]
 * 
 * Note:
 * 1 <= favoriteCompanies.length <= 100
 * 1 <= favoriteCompanies[i].length <= 500
 * 1 <= favoriteCompanies[i][j].length <= 20
 * All strings in favoriteCompanies[i] are distinct.
 * All lists of favorite companies are distinct, that is, If we sort alphabetically each list then favoriteCompanies[i] != favoriteCompanies[j].
 * All strings consist of lowercase English letters only.
 * 
 */
#include <vector>
#include <string>
#include <unordered_set>
using namespace std;

class Solution {
public:
    vector<int> peopleIndexes(vector<vector<string>>& favoriteCompanies) {
        int n = favoriteCompanies.size();
        vector<unordered_set<string>> sets(n);
        for (int i = 0; i < n; ++i) {
            sets[i] = unordered_set<string>(favoriteCompanies[i].begin(), favoriteCompanies[i].end());
        }

        vector<int> ans;
        for (int i = 0; i < n; ++i) {
            bool isSubset = false;
            for (int j = 0; j < n; ++j) {
                if (i == j) continue;
                // if size of i > size of j, cannot be subset (optimization)
                if (sets[i].size() > sets[j].size()) continue;
                // check if sets[i] is subset of sets[j]
                bool subset = true;
                for (const string& s : sets[i]) {
                    if (sets[j].find(s) == sets[j].end()) {
                        subset = false;
                        break;
                    }
                }
                if (subset) {
                    isSubset = true;
                    break;
                }
            }
            if (!isSubset) ans.push_back(i);
        }
        return ans;
    }
};