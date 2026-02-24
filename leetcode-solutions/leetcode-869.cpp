/**
 * 869. Reordered Power of 2
 * 
 * Example 1:
 * Input: 1
 * Output: true
 * 
 * Example 2:
 * Input: 10
 * Output: false
 * 
 * Example 3:
 * Input: 16
 * Output: true
 * 
 * Example 4:
 * Input: 24
 * Output: false
 * 
 * Example 5:
 * Input: 46
 * Output: true
 * 
 * Note:
 * 1 <= N <= 10^9
 * 
 */
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    bool reorderedPowerOf2(int N) {
        // Count digits of N
        string s = to_string(N);
        vector<int> cnt(10, 0);
        for (char c : s) cnt[c - '0']++;
        int len = s.size();

        // Check all powers of 2 up to 2^33 (largest 10-digit power)
        for (int i = 0; i <= 33; ++i) {
            long long p = 1LL << i;          // 2^i
            string sp = to_string(p);
            if (sp.size() != len) continue;  // must have same number of digits

            vector<int> cntp(10, 0);
            for (char c : sp) cntp[c - '0']++;

            if (cnt == cntp) return true;
        }
        return false;
    }
};