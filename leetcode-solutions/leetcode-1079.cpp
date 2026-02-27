/*
 * 1079. Letter Tile Possibilities
 *
 * You have a set of tiles, where each tile has one letter tiles[i] printed on it.  Return the number of possible non-empty sequences of letters you can make.
 * 
 * Example 1:
 * Input: "AAB"
 * Output: 8
 * Explanation: The possible sequences are "A", "B", "AA", "AB", "BA", "AAB", "ABA", "BAA".
 * 
 * Example 2:
 * Input: "AAABBC"
 * Output: 188
 * 
 * Note:
 * 1 <= tiles.length <= 7
 * tiles consists of uppercase English letters.
 * 
 */
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    int numTilePossibilities(string tiles) {
        // 统计每个字母的频率
        vector<int> freq(26, 0);
        for (char c : tiles) {
            freq[c - 'A']++;
        }
        
        // 使用回溯法计算所有可能的序列
        return backtrack(freq);
    }
    
private:
    int backtrack(vector<int>& freq) {
        int count = 0;
        
        // 遍历所有可能的字母
        for (int i = 0; i < 26; i++) {
            if (freq[i] > 0) {
                // 选择当前字母
                freq[i]--;
                // 当前选择本身就是一个有效序列
                count++;
                // 递归探索更长的序列
                count += backtrack(freq);
                // 回溯：恢复字母计数
                freq[i]++;
            }
        }
        
        return count;
    }
};