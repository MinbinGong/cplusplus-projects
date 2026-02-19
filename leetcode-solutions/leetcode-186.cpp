/*
 * Reverse Words in a String II
 * 
 * Given a character array s, reverse the order of the words.
 * 
 * A word is defined as a sequence of non-space characters. The words in s will be separated by a single space.
 * 
 * Your code must solve the problem in-place, i.e. without allocating extra space.
 * 
 * Constraints:
 * 1. 1 <= s.length <= 105
 * 2. s[i] is an English letter (uppercase or lowercase), digit, or space ' '.
 * 3. There is at least one word in s.
 * 4. s does not contain leading or trailing spaces.
 * 5. All the words in s are guaranteed to be separated by a single space.
 * 6. s consists of only lowercase English letters.
 */
#include <vector>
using namespace std;

void reverseString(vector<char>& s, int start, int end) {
    while (start < end) {
        swap(s[start], s[end]);
        start++;
        end--;
    }
}
void reverseWords(vector<char>& s) {
    // 1. 翻转整个字符串
    reverseString(s, 0, s.size() - 1);

    int n = s.size();
    int left = 0;
    // 2. 逐个翻转每个单词
    for (int right = 0; right <= n; ++right) {
        // 遇到空格或到达末尾，说明找到了一个单词
        if (right == n || s[right] == ' ') {
            // 翻转单词区间 [left, right-1]
            reverseString(s, left, right - 1);
            // 更新下一个单词的起点
            left = right + 1;
        }
    }
}