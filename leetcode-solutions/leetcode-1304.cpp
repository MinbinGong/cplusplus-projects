/*
 * 1304. Find N Unique Integers Sum up to Zero
 * 
 * Given an integer n, return any array containing n unique integers such that they add up to 0.
 * 
 * Example 1:
 * Input: n = 5
 * Output: [-7,-1,1,3,4]
 * Explanation: These arrays also are accepted [-5,-1,1,2,3] , [-3,-1,2,-2,4].
 * 
 * Example 2:
 * Input: n = 3
 * Output: [-1,0,1]
 * 
 * Example 3:
 * Input: n = 1
 * Output: [0]
 * 
 * Note:
 * 1 <= n <= 1000
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> sumZero(int n) {
        vector<int> result;
        // 添加相反数对
        for (int i = 1; i <= n / 2; ++i) {
            result.push_back(i);
            result.push_back(-i);
        }
        // 如果 n 是奇数，再添加一个 0
        if (n % 2 == 1) {
            result.push_back(0);
        }
        return result;
    }
};