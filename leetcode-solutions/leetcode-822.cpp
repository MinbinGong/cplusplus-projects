/**
 * 822. Card Flipping Game
 *
 * You are given two 0-indexed integer arrays fronts and backs of length n, where the ith card has the positive integer fronts[i] printed on the front and backs[i] printed on the back. Initially, each card is placed on a table such that the front number is facing up and the other is facing down. You may flip over any number of cards (possibly zero).
 *
 * After flipping, the front number of the card is now facing up, and the back number is now facing down.
 *
 * An integer x is said to be good if it is facing down on some card and x is not facing up on any card.
 *
 * Return the minimum possible good integer after flipping the cards. If there are no good integers, return 0.
 *
 * Example:
 * Input: fronts = [1,2,4,4,7], backs = [1,3,4,1,3]
 * Output: 2
 * Explanation:
 * 
 * Note:
 * 1 <= fronts.length <= 1000
 * 1 <= fronts[i], backs[i] <= 2000
 */
#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>
using namespace std;

class Solution {
public:
    int flipgame(vector<int>& fronts, vector<int>& backs) {
        unordered_set<int> all;
        unordered_set<int> same;
        int n = fronts.size();
        for (int i = 0; i < n; ++i) {
            all.insert(fronts[i]);
            all.insert(backs[i]);
            if (fronts[i] == backs[i]) {
                same.insert(fronts[i]);
            }
        }
        int ans = INT_MAX;
        for (int x : all) {
            if (!same.count(x)) {
                ans = min(ans, x);
            }
        }
        return ans == INT_MAX ? 0 : ans;
    }
};