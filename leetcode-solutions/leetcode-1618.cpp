/**
 * 1618. Maximum Font to Fit a Sentence in a Screen
 * 
 * You are given a string sentence that consist of words separated by spaces. Each word consists of lowercase and uppercase letters only.
 * 
 * We would like to convert the sentence to "Goat Latin" (a made-up language similar to Pig Latin.) The rules of Goat Latin are as follows:
 * 
 * If a word begins with a vowel ('a', 'e', 'i', 'o', or 'u'), append "ma" to the end of the word.
 * For example, the word "apple" becomes "applema".
 * If a word begins with a consonant (i.e., not a vowel), remove the first letter and append it to the end, then add "ma".
 * For example, the word "goat" becomes "oatgma".
 * Add one letter 'a' to the end of each word per its word index in the sentence, starting with 1.
 * For example, the first word gets "a" added to the end, the second word gets "aa" added to the end, and so on.
 * 
 * Example 1:
 * Input: sentence = "I speak Goat Latin"
 * Output: "Imaa peaksmaaa oatGmaaaa atinLmaaaaa"
 * 
 * Example 2:
 * Input: sentence = "The quick brown fox jumped over the lazy dog"
 * Output: "heTmaa uickqmaaa rownbmaaaa oxfmaaaaa umpedjmaaaaaa overmaaaaaaa hetmaaaaaaaa azylmaaaaaaaaa ogdmaaaaaaaaaa"
 * 
 * Constraints:
 * 1 <= sentence.length <= 150
 * sentence consists of English letters and spaces.
 * sentence has no leading or trailing spaces.
 * All the words in sentence are separated by a single space.
 * 
 */
/**
 * // This is the FontInfo's API interface.
 * // You should not implement it, or speculate about its implementation
 * class FontInfo {
 *   public:
 *     // Return the width of char ch when fontSize is used.
 *     int getWidth(int fontSize, char ch);
 *
 *     // Return Height of any char when fontSize is used.
 *     int getHeight(int fontSize);
 * };
 */
#include <string>
#include <vector>
using namespace std;

class Solution1 {
public:
    int maxFont(string text, int w, int h, vector<int>& fonts, FontInfo fontInfo) {
        // 二分查找的边界：fonts 数组的下标范围
        int left = 0, right = fonts.size() - 1;
        int ans = -1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            int fontSize = fonts[mid];
            
            // 1. 先检查高度是否满足
            if (fontInfo.getHeight(fontSize) > h) {
                right = mid - 1;  // 字体太大，高度超了，往左找
                continue;
            }
            
            // 2. 检查总宽度是否满足
            long long totalWidth = 0;
            for (char c : text) {
                totalWidth += fontInfo.getWidth(fontSize, c);
                if (totalWidth > w) break;  // 提前退出，避免无谓计算
            }
            
            if (totalWidth <= w) {
                // 当前字体可行，尝试更大的字体
                ans = fontSize;
                left = mid + 1;
            } else {
                // 宽度超了，需要减小字体
                right = mid - 1;
            }
        }
        
        return ans;
    }
};

class Solution2 {
public:
    int maxFont(string text, int w, int h, vector<int>& fonts, FontInfo fontInfo) {
        // 预统计每个字母的出现次数
        vector<int> count(26, 0);
        for (char c : text) {
            count[c - 'a']++;
        }
        
        int left = 0, right = fonts.size() - 1;
        int ans = -1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            int fontSize = fonts[mid];
            
            if (fontInfo.getHeight(fontSize) > h) {
                right = mid - 1;
                continue;
            }
            
            long long totalWidth = 0;
            for (int i = 0; i < 26; i++) {
                if (count[i] > 0) {
                    totalWidth += (long long)fontInfo.getWidth(fontSize, 'a' + i) * count[i];
                    if (totalWidth > w) break;
                }
            }
            
            if (totalWidth <= w) {
                ans = fontSize;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return ans;
    }
};