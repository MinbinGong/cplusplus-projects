/*
 * Flip Game
 * 
 * You are playing the following Flip Game with your friend:
 * 
 * Given a string that contains only these two characters: + and -, you and your friend take turns to flip two consecutive "++" into "--".
 * The game ends when a person can no longer make a move and therefore the other person will be the winner.
 * 
 * Write a function to compute all possible states of the string after one valid move.
 * 
 * Example:
 * Input: s = "++++"
 * Output: 
 * [
 *   "--++",
 *   "+--+",
 *   "++--"
 * ]
 * 
 * Note: If there is no valid move, return an empty list [].
 * 
 */
#include <string>
#include <vector>
using namespace std;

// Solution1: 模拟翻转操作
class Solution1 {
public:
    vector<string> generatePossibleNextMoves(string s) {
        vector<string> res;
        int n = s.size();
        for (int i = 0; i < n - 1; ++i) {
            // 找到连续的两个 '+'
            if (s[i] == '+' && s[i + 1] == '+') {
                // 执行翻转操作
                s[i] = s[i + 1] = '-';
                // 记录新状态
                res.push_back(s);
                // 回溯：恢复原状，继续寻找下一个可能的位置
                s[i] = s[i + 1] = '+';
            }
        }
        return res;
    }
};

// Solution2: 直接构造新字符串
class Solution2 {
public:
    vector<string> generatePossibleNextMoves(string s) {
        vector<string> res;
        for (int i = 1; i < s.size(); ++i) {
            if (s[i] == '+' && s[i - 1] == '+') {
                // 构造新字符串：前半部分 + "--" + 后半部分
                string newState = s.substr(0, i - 1) + "--" + s.substr(i + 1);
                res.push_back(newState);
            }
        }
        return res;
    }
};