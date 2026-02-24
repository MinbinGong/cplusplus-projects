/**
 * 899. Orderly Queue
 *
 * A string S of lowercase letters is given.  Then, we may make any number of moves.
 * In each move, we choose one of the first K letters (starting from the left), remove it, and place it at the end of the string.
 * Return the lexicographically smallest string we could have after any number of moves.
 *
 * Example 1:
 * Input: S = "cba", K = 1
 * Output: "acb"
 * Explanation: 
 * In the first move, we move the 1st character ("c") to the end, obtaining the string "bac".
 * In the second move, we move the 1st character ("b") to the end, obtaining the final result "acb".
 *
 * Example 2:
 * Input: S = "baaca", K = 3
 * Output: "aaabc"
 * Explanation: 
 * In the first move, we move the 1st character ("b") to the end, obtaining the string "aacab".
 * In the second move, we move the 3rd character ("c") to the end, obtaining the string "aaabc".
 * In the third move, we move the 1st character ("a") to the end, obtaining the final result "aaabc".
 *
 * Note:
 * 1 <= K <= S.length <= 1000
 * S consists of lowercase letters only.
 * 
 */
#include <string>
#include <algorithm>
using namespace std;

class Solution {
public:
    string orderlyQueue(string s, int k) {
        if (k == 1) {
            // 只有一种操作：循环移位，找出所有循环移位中的最小字典序
            string ans = s;
            int n = s.size();
            for (int i = 1; i < n; ++i) {
                string cur = s.substr(i) + s.substr(0, i);
                if (cur < ans) ans = cur;
            }
            return ans;
        } else {
            // k >= 2 时可以任意重排，直接排序得到最小字典序
            sort(s.begin(), s.end());
            return s;
        }
    }
};