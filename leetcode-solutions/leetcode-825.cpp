/**
 * 825. Friends Of Appropriate Ages
 *
 * Some people will make friend requests. The list of their ages is given and ages[i] is the age of the ith person.
 *
 * Person A will NOT friend request person B (B != A) if any of the following conditions are true:
 *
 * age[B] <= 0.5 * age[A] + 7
 * age[B] > age[A]
 * age[B] > 100 && age[A] < 100
 * Otherwise, A will friend request B.
 *
 * Note that if A requests B, B does not necessarily request A.  Also, people will not friend request themselves.
 *
 * How many total friend requests are made?
 *
 * Example:
 * Input: [16,16]
 * Output: 2
 * Explanation: 2 people friend request each other.
 *
 * Input: [16,17,18]
 * Output: 2
 * Explanation: Friend requests are made 17 -> 16, 18 -> 17.
 * 
 * Input: [20,30,100,110,120]
 * Output: 3
 * Explanation: Friend requests are made 110 -> 100, 120 -> 110, 120 -> 100.
 * 
 * Note:
 * 1 <= ages.length <= 20000.
 * 1 <= ages[i] <= 120.
 */
#include <vector>
using namespace std;

class Solution {
public:
    int numFriendRequests(vector<int>& ages) {
        vector<int> count(121, 0);          // 年龄范围 1~120
        for (int age : ages) {
            count[age]++;
        }
        int res = 0;
        for (int a = 1; a <= 120; a++) {
            for (int b = 1; b <= 120; b++) {
                if (count[a] == 0 || count[b] == 0) continue;
                // 条件判断，转换为整数避免浮点精度
                if (2 * b <= a + 14) continue;   // b <= 0.5*a + 7
                if (b > a) continue;              // b > a
                if (b > 100 && a < 100) continue; // b>100 且 a<100
                if (a == b) {
                    res += count[a] * (count[a] - 1); // 不能给自己发
                } else {
                    res += count[a] * count[b];
                }
            }
        }
        return res;
    }
};