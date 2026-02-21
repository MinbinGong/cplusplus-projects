/*
 * Sentence Screen Fitting
 *
 * Given a rows x cols screen and a sentence represented by a list of non-empty words, find how many times the given sentence can be fitted on the screen.
 *
 * Note:
 * A word cannot be split into two lines.
 * The order of words in the sentence must remain unchanged.
 * Two consecutive words in a line must be separated by a single space.
 * Total words in the sentence won't exceed 100.
 * Length of each word is greater than 0 and won't exceed 10.
 * 1 ≤ rows, cols ≤ 20,000.
 *
 * Example 1:
 * Input:
 * rows = 2, cols = 8, sentence = ["hello", "world"]
 *
 * Output: 
 * 1
 *
 * Explanation:
 * hello---
 * world---
 *
 * The character '-' signifies an empty space on the screen.
 * 
 * Constraints:
 * 1 <= rows, cols <= 20,000.
 * 1 <= sentence.length <= 100.
 * 1 <= sentence[i].length <= 10.
 * sentence[i] consists of lowercase English letters.
 * sentence is guaranteed to fit within a single line on the screen.
 * 
 */
#include <vector>
#include <string>
#include <unordered_map>
#include <utility>
using namespace std;

class Solution1 {
public:
    int wordsTyping(vector<string>& sentence, int rows, int cols) {
        // 1. 将句子拼接成一个长字符串，单词间加空格，末尾也加空格
        string s;
        for (const auto& word : sentence) {
            s += word + " ";
        }
        int len = s.size();        // 循环字符串的长度
        
        int start = 0;              // 指向当前已填充字符的总数（位置指针）
        for (int i = 0; i < rows; ++i) {
            start += cols;          // 先假设当前行填满 cols 个字符
            
            // 检查当前行末尾的下一个字符（即下一行起始字符）
            if (s[start % len] == ' ') {
                // 如果正好是空格，说明单词完整结束，可以将该空格“吞掉”
                ++start;
            } else {
                // 如果落在单词中间，需要回退到前一个空格（单词开头）
                while (start > 0 && s[(start - 1) % len] != ' ') {
                    --start;
                }
            }
        }
        // 总共填充的字符数除以循环字符串长度，即为完整显示的次数
        return start / len;
    }
};

class Solution2 {
public:
    int wordsTyping(vector<string>& sentence, int rows, int cols) {
        int n = sentence.size();
        unordered_map<int, pair<int, int>> cache; // key: 起始单词下标, value: {该行能放的单词数, 下一行起始单词下标}

        int wordCount = 0;          // 总共放置的单词数
        int startIdx = 0;           // 当前行的起始单词下标

        for (int i = 0; i < rows; ++i) {
            if (cache.count(startIdx)) {
                // 如果已经缓存过，直接使用
                wordCount += cache[startIdx].first;
                startIdx = cache[startIdx].second;
            } else {
                // 否则模拟这一行
                int col = 0;
                int cnt = 0;
                int cur = startIdx;
                while (col + sentence[cur].size() <= cols) {
                    col += sentence[cur].size() + 1; // 加1代表空格
                    cur = (cur + 1) % n;
                    cnt++;
                }
                // 存入缓存
                cache[startIdx] = {cnt, cur};
                wordCount += cnt;
                startIdx = cur;
            }
        }
        return wordCount / n;
    }
};