/**
 * 1324. Print Words Vertically
 * 
 * Given a string s. Return all the words vertically in the same order in which they appear in s.
 * Words are returned as a list of strings, complete with spaces when is necessary. (Trailing spaces are not allowed).
 * Each word would be put on only one column and that in one column there will be only one word.
 * 
 * Example 1:
 * Input: s = "HOW ARE YOU"
 * Output: ["HAY","ORO","WEU"]
 * 
 * Example 2:
 * Input: s = "TO BE OR NOT TO BE"
 * Output: ["TBONTB","OEROOE","   T"]
 * 
 * Example 3:
 * Input: s = "CONTEST IS COMING"
 * Output: ["CIC","OSO","N M","T I","E N","S G","T"]
 * 
 * Note:
 * 1 <= s.length <= 100
 * s contains only upper case English letters.
 * It's guaranteed that there is only one space between 2 words.
 * 
 */
#include <vector>
#include <string>
#include <sstream>
using namespace std;

class Solution {
public:
    vector<string> printVertically(string s) {
        vector<string> words;
        istringstream iss(s);
        string word;
        int maxLen = 0;
        // 分割单词并记录最大长度
        while (iss >> word) {
            words.push_back(word);
            if (word.size() > maxLen) maxLen = word.size();
        }
        
        vector<string> result;
        for (int i = 0; i < maxLen; ++i) {
            string col;
            for (const string& w : words) {
                if (i < w.size()) col += w[i];
                else col += ' ';
            }
            // 去除末尾空格
            while (!col.empty() && col.back() == ' ') {
                col.pop_back();
            }
            result.push_back(col);
        }
        return result;
    }
};