/**
 * 1138. Alphabet Board Path
 * Medium
 * 
 * (This problem is an interactive problem.)
 * 
 * On an alphabet board, we start at position (0, 0), corresponding to character board[0][0].
 * 
 * Here, board = ["abcde", "fghij", "klmno", "pqrst", "uvwxy", "z"], as shown in the diagram below.
 * 
 * We may make the following moves:
 * 
 * 'U' moves our position up one row, if the position exists on the board;
 * 'D' moves our position down one row, if the position exists on the board;
 * 'L' moves our position left one column, if the position exists on the board;
 * 'R' moves our position right one column, if the position exists on the board;
 * '!' adds the character board[r][c] at our current position (r, c) to the answer.
 * (Here, the only positions that exist on the board are positions with letters on them.)
 * 
 * (Note that '!' does not move anywhere, as it has no position on the board.)
 * 
 * Return a sequence of moves that makes our answer equal to target in the minimum number of moves.  You may return any path that does so.
 * 
 * Example 1:
 * Input: target = "leet"
 * Output: "DDR!UURRR!!DDD!"
 * 
 * Example 2:
 * Input: target = "code"
 * Output: "RR!DDRR!UUL!R!"
 * 
 * Note:
 * 1 <= target.length <= 100
 * target consists only of English lowercase letters.
 * 
 */
#include <string>
using namespace std;

class Solution {
public:
    string alphabetBoardPath(string target) {
        string res;
        int r = 0, c = 0; // 当前位置的行和列
        for (char ch : target) {
            int idx = ch - 'a';
            int nr = idx / 5;   // 目标行，每行5个字母
            int nc = idx % 5;   // 目标列

            // 移动顺序：先上，再左，再右，最后下（保证不会走到非法格子）
            while (r > nr) { res += 'U'; r--; }
            while (c > nc) { res += 'L'; c--; }
            while (c < nc) { res += 'R'; c++; }
            while (r < nr) { res += 'D'; r++; }

            res += '!'; // 标记选取当前字母
        }
        return res;
    }
};