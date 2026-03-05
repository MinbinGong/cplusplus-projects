/**
 * 1592. Rearrange Spaces Between Words
 * 
 * You are given a string text of words that are placed among some number of spaces. Each word consists of one or more lowercase English letters and are separated by at least one space. It's guaranteed that text contains at least one word.
 * 
 * Rearrange the spaces so that there is an equal number of spaces between every pair of adjacent words and that number is maximized. If you cannot redistribute all the spaces equally, place the extra spaces at the end, meaning the returned string should be the same length as text.
 * 
 * Return the string after rearranging the spaces.
 * 
 * Example 1: 
 * 
 */
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    string reorderSpaces(string text) {
        int spaces = 0;
        vector<string> words;
        int n = text.size();
        
        // 统计空格并提取单词
        for (int i = 0; i < n; ) {
            if (text[i] == ' ') {
                ++spaces;
                ++i;
            } else {
                int j = i;
                while (j < n && text[j] != ' ') ++j;
                words.push_back(text.substr(i, j - i));
                i = j;
            }
        }
        
        int wordCount = words.size();
        if (wordCount == 1) {
            // 只有一个单词，所有空格放在末尾
            return words[0] + string(spaces, ' ');
        }
        
        int each = spaces / (wordCount - 1);  // 单词间平均空格数
        int extra = spaces % (wordCount - 1); // 多余的空格放在末尾
        
        string result;
        for (int i = 0; i < wordCount; ++i) {
            if (i > 0) result += string(each, ' ');
            result += words[i];
        }
        result += string(extra, ' ');
        
        return result;
    }
};