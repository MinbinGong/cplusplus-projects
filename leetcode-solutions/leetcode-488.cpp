/*
 * Zuma Game
 *
 *  You are playing a variation of the Zuma game.
 *
 *  In this variation of Zuma, there is a single row of colored balls on a board, where each ball can be colored red 'R', yellow 'Y', blue 'B', green 'G', or white 'W'. You also have several colored balls in your hand.
 *
 *  Your goal is to clear all of the balls from the board. On each turn:
 *
 *  Pick any ball from your hand and insert it in between two balls in the row or on either end of the row.
 *  If there is a group of three or more consecutive balls of the same color, remove the group of balls from the board.
 *  If this removal causes more groups of three or more of the same color to form, then continue removing each group until there are none left.
 *  If there are no more balls on the board, then you win the game.
 *  Repeat this process until you either win or do not have any more balls in your hand.
 * 
 * Constraints:
 * 1 <= board.length <= 16
 * 1 <= hand.length <= 5
 * board and hand consist of the characters 'R', 'Y', 'B', 'G', and 'W'.
 * The initial row of balls on the board will not have any groups of three or more consecutive balls of the same color.
 * 
 */
#include <string>
#include <vector>
#include <unordered_map>
#include <climits>
#include <algorithm>

using namespace std;

class Solution {
public:
    int findMinStep(string board, string hand) {
        vector<int> handCount(5, 0);
        for (char c : hand) {
            handCount[colorToIndex(c)]++;
        }
        unordered_map<string, int> memo;
        int res = dfs(board, handCount, memo);
        return res == INT_MAX ? -1 : res;
    }

private:
    int colorToIndex(char c) {
        switch (c) {
            case 'R': return 0;
            case 'Y': return 1;
            case 'B': return 2;
            case 'G': return 3;
            case 'W': return 4;
            default: return -1;
        }
    }

    char indexToColor(int i) {
        static const string colors = "RYBGW";
        return colors[i];
    }

    string encodeKey(const string& board, const vector<int>& hand) {
        string key = board + "#";
        for (int i = 0; i < 5; ++i) {
            key += to_string(hand[i]) + ",";
        }
        return key;
    }

    // Remove all runs of three or more consecutive same letters repeatedly
    string reduce(const string& s) {
        string cur = s;
        while (true) {
            bool removed = false;
            string next;
            int i = 0;
            while (i < cur.size()) {
                int j = i;
                while (j < cur.size() && cur[j] == cur[i]) ++j;
                if (j - i >= 3) {
                    removed = true;   // skip this run
                } else {
                    next += cur.substr(i, j - i);
                }
                i = j;
            }
            if (!removed) break;
            cur = next;
        }
        return cur;
    }

    int dfs(const string& board, vector<int>& hand, unordered_map<string, int>& memo) {
        if (board.empty()) return 0;
        string key = encodeKey(board, hand);
        if (memo.count(key)) return memo[key];

        int best = INT_MAX;
        // Try inserting each available color at every possible position
        for (int pos = 0; pos <= board.size(); ++pos) {
            for (int c = 0; c < 5; ++c) {
                if (hand[c] == 0) continue;

                string newBoard = board;
                newBoard.insert(pos, 1, indexToColor(c));
                newBoard = reduce(newBoard);

                hand[c]--;
                int steps = dfs(newBoard, hand, memo);
                if (steps != -1) {
                    best = min(best, 1 + steps);
                }
                hand[c]++;
            }
        }

        memo[key] = (best == INT_MAX ? -1 : best);
        return memo[key];
    }
};