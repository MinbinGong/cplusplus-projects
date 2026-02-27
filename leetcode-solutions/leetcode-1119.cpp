/*
 * 1119. Remove Vowels from a String
 * 
 * Given a string s, remove the vowels 'a', 'e', 'i', 'o', and 'u' from it, and return the new string.
 * 
 * 1 <= s.length <= 1000
 * s consists of only lowercase English letters.
 */
#include <string>
#include <sstream>
#include <regex>

using namespace std;

class Solution1 {
public:
    string removeVowels(string s) {
        string result;
        
        // 遍历字符串，只添加非元音字符
        for (char c : s) {
            if (!isVowel(c)) {
                result += c;
            }
        }
        
        return result;
    }
    
private:
    // 辅助函数：判断字符是否为元音
    bool isVowel(char c) {
        // 检查小写和大写元音
        return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
               c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U';
    }
};

class Solution2 {
public:
    string removeVowels(string s) {
        // 使用remove_if和erase组合
        auto isVowel = [](char c) {
            c = tolower(c);
            return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
        };
        
        s.erase(remove_if(s.begin(), s.end(), isVowel), s.end());
        return s;
    }
};

class Solution3 {
public:
    string removeVowels(string s) {
        stringstream ss;
        for (char c : s) {
            if (!(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
                  c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U')) {
                ss << c;
            }
        }
        return ss.str();
    }
};

class Solution4 {
public:
    string removeVowels(string s) {
        // 匹配所有元音字母（大小写）
        regex pattern("[aeiouAEIOU]");
        return regex_replace(s, pattern, "");
    }
};

class Solution5 {
public:
    string removeVowels(string s) {
        int write = 0;  // 写入位置
        
        for (int read = 0; read < s.length(); read++) {
            char c = s[read];
            // 如果不是元音，复制到写入位置
            if (!(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
                  c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U')) {
                s[write++] = c;
            }
        }
        
        // 截断字符串
        s.resize(write);
        return s;
    }
};