/*
 * Strobogrammatic Number II 
 * 
 * A strobogrammatic number is a number that looks the same when rotated 180 degrees (looked at upside down).
 * 
 * Write a function to find all strobogrammatic numbers that are of length n.
 * 
 * Constraints:
 * 1. 1 <= n <= 14
 */
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    vector<string> findStrobogrammatic(int n) {
        vector<string> result;
        vector<char> path(n);
        dfs(result, path, 0, n - 1, n);
        return result;
    }

private:
    const vector<char> singles = {'0', '1', '8'};
    const vector<pair<char, char>> pairs = {
        {'0', '0'}, {'1', '1'}, {'6', '9'}, {'8', '8'}, {'9', '6'}
    };
    
    void dfs(vector<string>& result, vector<char>& path, int left, int right, int n) {
        if (left > right) {
            result.push_back(string(path.begin(), path.end()));
            return;
        }
        
        if (left == right) {
            // Middle position for odd length
            for (char c : singles) {
                path[left] = c;
                dfs(result, path, left + 1, right - 1, n);
            }
        } else {
            for (const auto& p : pairs) {
                // Skip leading zero
                if (left == 0 && p.first == '0') continue;
                
                path[left] = p.first;
                path[right] = p.second;
                dfs(result, path, left + 1, right - 1, n);
            }
        }
    }
};