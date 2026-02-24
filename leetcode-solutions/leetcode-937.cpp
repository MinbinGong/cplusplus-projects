/*
 * Reorder Log Files
 *
 * You have an array of logs.  Each log is a space delimited string of words.
 *
 * For each log, the first word in each log is an alphanumeric identifier.  Then, either:
 *
 * Each word after the identifier will consist only of lowercase letters, or;
 * Each word after the identifier will consist only of digits.
 * We will call these two varieties of logs letter-logs and digit-logs.  It is guaranteed that each log has at least one word after its identifier.
 *
 * Reorder the logs so that all of the letter-logs come before any digit-log.  The letter-logs are ordered lexicographically ignoring identifier, with the identifier used in case of ties.  The digit-logs should be put in their original order.
 *
 * Return the final order of the logs.
 *
 * Example 1:
 * Input: logs = ["dig1 8 1 5 1","let1 art can","dig2 3 6","let2 own kit dig","let3 art zero"]
 * Output: ["let1 art can","let3 art zero","let2 own kit dig","dig1 8 1 5 1","dig2 3 6"]
 * 
 * Note:
 * 0 <= logs.length <= 100
 * 3 <= logs[i].length <= 100
 * logs[i] is guaranteed to have an identifier, and a word after the identifier.
 * 
 */
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<string> reorderLogFiles(vector<string>& logs) {
        // 稳定排序：字母日志在前，数字日志在后，且字母日志按内容排序
        stable_sort(logs.begin(), logs.end(), [](const string& a, const string& b) {
            // 找到第一个空格，分割标识符和内容
            int posA = a.find(' ');
            int posB = b.find(' ');
            
            string idA = a.substr(0, posA);
            string idB = b.substr(0, posB);
            string contentA = a.substr(posA + 1);
            string contentB = b.substr(posB + 1);
            
            // 判断是否为数字日志：内容第一个字符是数字
            bool isDigitA = isdigit(contentA[0]);
            bool isDigitB = isdigit(contentB[0]);
            
            if (isDigitA && isDigitB) {
                // 两个都是数字日志，保持原有顺序（稳定排序保证）
                return false; // 返回false表示a不小于b，即不交换
            } else if (!isDigitA && !isDigitB) {
                // 两个都是字母日志，按内容字典序，相同则按标识符
                if (contentA != contentB) {
                    return contentA < contentB;
                } else {
                    return idA < idB;
                }
            } else {
                // 一个字母一个数字：字母日志应该排在数字日志前面
                // 如果a是字母，b是数字，则a应该小于b（返回true表示a<b）
                // 如果a是数字，b是字母，则a应该大于b（返回false）
                return !isDigitA; // 当isDigitA为false（a是字母）时返回true
            }
        });
        return logs;
    }
};