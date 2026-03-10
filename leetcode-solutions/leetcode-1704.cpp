/*
 * 1704. Determine if String Halves Are Alike
 * 
 * You are given a string s of even length. Split this string into two halves of equal lengths, and let a be the first half and b be the second half.
 * 
 * Two strings are alike if they have the same number of vowels ('a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'). Notice that s contains uppercase and lowercase letters.
 * 
 * Return true if a and b are alike. Otherwise, return false.
 * 
 * Example 1:
 * Input: s = "book"
 * Output: true
 * Explanation: a = "bo" and b = "ok". a has 1 vowel and b has 1 vowel. Therefore, they are alike.
 * 
 * Example 2:
 * Input: s = "textbook"
 * Output: false
 * Explanation: a = "text" and b = "book". a has 1 vowel whereas b has 2. Therefore, they are not alike.
 * Notice that the vowel o is counted twice.
 * 
 * Constraints:
 * 2 <= s.length <= 1000
 * s.length is even.
 * s consists of uppercase and lowercase letters.
 * 
 */
#include <string>
using namespace std;

class Solution1 {
public:
    bool halvesAreAlike(string s) {
        int n = s.length();
        int half = n / 2;
        string a = s.substr(0, half);
        string b = s.substr(half);
        
        auto countVowels = [](const string& str) {
            int cnt = 0;
            for (char c : str) {
                c = tolower(c); // 统一转小写方便判断
                if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
                    cnt++;
            }
            return cnt;
        };
        
        return countVowels(a) == countVowels(b);
    }
};

class Solution2 {
public:
    bool halvesAreAlike(string s) {
        int n = s.length();
        int half = n / 2;
        int cnt = 0;
        auto isVowel = [](char c) {
            c = tolower(c);
            return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
        };
        for (int i = 0; i < half; ++i) {
            if (isVowel(s[i])) cnt++;
        }
        for (int i = half; i < n; ++i) {
            if (isVowel(s[i])) cnt--;
        }
        return cnt == 0;
    }
};