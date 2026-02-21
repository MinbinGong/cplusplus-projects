/*
 *  Keyboard Row
 *
 *  Given an array of strings words, return the words that can be typed using letters of the alphabet on only one row of American keyboard like the image below.
 *
 *  In the American keyboard:
 *
 *  the first row consists of the characters "qwertyuiop",
 *  the second row consists of the characters "asdfghjkl", and
 *  the third row consists of the characters "zxcvbnm".
 *
 *  Constraints:
 *  1 <= words.length <= 20
 *  1 <= words[i].length <= 100
 *  words[i] consists of English letters (both lowercase and uppercase).
 * 
 */
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

class Solution {
public:
    vector<string> findWords(vector<string>& words) {
        // 定义键盘三行的字符
        vector<string> rows = {"qwertyuiop", "asdfghjkl", "zxcvbnm"};
        unordered_map<char, int> rowMap; // 字符 -> 行号

        // 构建映射，同时处理大小写
        for (int i = 0; i < rows.size(); ++i) {
            for (char c : rows[i]) {
                rowMap[c] = i;
                rowMap[toupper(c)] = i;
            }
        }

        vector<string> result;
        for (const string& word : words) {
            if (word.empty()) continue;
            int firstRow = rowMap[word[0]];
            bool valid = true;
            for (char c : word) {
                if (rowMap[c] != firstRow) {
                    valid = false;
                    break;
                }
            }
            if (valid) {
                result.push_back(word);
            }
        }
        return result;
    }
};