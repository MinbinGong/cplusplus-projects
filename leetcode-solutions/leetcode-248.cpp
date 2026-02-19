/*
 * Strobogrammatic Number III
 * 
 * A strobogrammatic number is a number that looks the same when rotated 180 degrees (looked at upside down).
 * 
 * Write a function to count the total strobogrammatic numbers that exist in the range [low, high].
 * 
 * Constraints:
 * 1. 1 <= low.length <= high.length <= 14
 * 2. low and high consist of only digits.
 * 3. low and high do not contain any leading zeros.
 * 4. low <= high
 */
#include <vector>
#include <string>
using namespace std;

class Solution {
private:
    const vector<string> l = {"0", "1", "6", "8", "9"};
    const vector<string> r = {"0", "1", "9", "8", "6"};
    int ans = 0;
    
    void dfs(string num, string& low, string& high) {
        if (num.size() > high.size()) return;
        
        if (num.size() >= low.size() && num.size() <= high.size()) {
            // Check bounds
            if (num.size() == low.size() && num < low) return;
            if (num.size() == high.size() && num > high) return;
            
            // Count only if no leading zero (except single digit)
            if (num.size() == 1 || num[0] != '0') {
                ans++;
            }
        }
        
        // Build larger numbers by adding pairs at both ends
        for (int i = 0; i < 5; ++i) {
            dfs(l[i] + num + r[i], low, high);
        }
    }
    
public:
    int strobogrammaticInRange(string low, string high) {
        if (low.size() > high.size() || 
            (low.size() == high.size() && low > high)) {
            return 0;
        }
        
        ans = 0;
        // Start DFS from base cases
        dfs("", low, high);
        dfs("0", low, high);
        dfs("1", low, high);
        dfs("8", low, high);
        
        return ans;
    }
};