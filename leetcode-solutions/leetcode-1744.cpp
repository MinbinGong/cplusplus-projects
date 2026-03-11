/*
 * 1744. Can You Eat Your Favorite Candy on Your Favorite Day?
 *
 * You are given a (0-indexed) array of positive integers candiesCount where
 * candiesCount[i] represents the number of candies of the ith type you have.
 * You are also given a 2D array queries where queries[i] = [favoriteTypei,
 * favoriteDayi, dailyCapi].
 * 
 * You play a game with the following rules:
 * 
 * You start eating candies on day 0.
 * You cannot eat any candy of type i unless you have eaten all candies of type
 * i - 1.
 * You must eat at least one candy per day until you have eaten all the
 * candies.
 * 
 * Construct a boolean array answer such that answer.length == queries.length
 * and answer[i] is true if you can eat a candy of type favoriteTypei on day
 * favoriteDayi without eating more than dailyCapi candies on any day, and
 * false otherwise. Note that you can eat different types of candy on the same
 * day, provided that you follow rule 2.
 * 
 * Return the constructed array answer.
 * 
 * Example 1:
 * 
 * Input: candiesCount = [7,4,5,3,8], queries = [[0,2,2],[4,2,4],[2,13,1000000000]]
 * Output: [true,false,true]
 * Explanation:
 * 1- If you eat 2 candies (type 0) on day 0 and 2 candies (type 0) on day 1,
 * you will eat a candy of type 0 on day 2.
 * 2- You can eat at most 4 candies each day.
 *    If you eat 4 candies every day, you will eat 4 candies (type 0) on day 0,
 *    4 candies (type 0 and type 1) on day 1, and 4 candies (type 1 and type 2)
 *    on day 2.
 *    However, you can only eat 4 candies of type 1 and 2 per day.
 * 3- You cannot eat 4 candies of type 3 on day 3.
 * 
 * Example 2:
 * 
 * Input: candiesCount = [5,2,6,4,1], queries = [[3,1,2],[4,10,3],[3,10,100]]
 * Output: [false,true,true]
 * 
 * Explanation:
 * 1- You cannot eat any candy of type 3 on day 0.
 * 2- If you eat 1 candy (type 0) on day 0 and 2 candies (type 0) on day 1, you
 * will eat a candy of type 0 on day 2, and a candy of type 1 on day 3.
 * 3- You can eat at most 6 candies each day.
 *    If you eat 6 candies every day, you will eat 6 candies (type 0) on day 0,
 *    6 candies (type 0 and type 1) on day 1, and 6 candies (type 1 and type 2)
 *    on day 2.
 *    However, you can only eat 4 candies of type 1 and 2 per day.
 * 4- You can eat at most 1 candy per day.
 *    If you eat 1 candy every day, you will eat 1 candy of type 3 on day 3.
 * 
 * Constraints:
 * 
 * 1 <= candiesCount.length <= 105
 * 1 <= candiesCount[i] <= 105
 * 1 <= queries.length <= 105
 * queries[i].length == 3
 * 0 <= favoriteTypei < candiesCount.length
 * 0 <= favoriteDayi <= 109
 * 1 <= dailyCapi <= 109
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    vector<bool> canEat(vector<int>& candiesCount, vector<vector<int>>& queries) {
        int n = candiesCount.size();
        vector<long long> prefix(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            prefix[i + 1] = prefix[i] + candiesCount[i];
        }

        vector<bool> ans;
        for (auto& q : queries) {
            int type = q[0];
            long long day = q[1];
            long long cap = q[2];

            long long first = prefix[type];               // first index of type
            long long last = prefix[type + 1] - 1;        // last index of type

            long long L = max(0LL, first - cap + 1);
            long long U = min(last, day * cap);

            ans.push_back(L <= U);
        }
        return ans;
    }
};
