/*
 * 1813. Sentence Similarity III
 * 
 * You are given two strings sentence1 and sentence2, each representing a sentence composed of words. A sentence is a list of words that are separated by a single space with no leading or trailing spaces. Each word consists of only uppercase and lowercase English characters.
 * 
 * Two sentences s1 and s2 are considered similar if it is possible to insert an arbitrary sentence (possibly empty) inside one of these sentences such that the two sentences become equal. Note that the inserted sentence must be separated from existing words by spaces.
 * 
 * For example,
 * 
 * s1 = "Hello Jane" and s2 = "Hello my name is Jane" can be made equal by inserting "my name is" between "Hello" and "Jane" in s1.
 * s1 = "Frog cool" and s2 = "Frogs are cool" are not similar, since although there is a sentence "s are" inserted into s1, it is not separated from "Frog" by a space.
 * 
 * Example 1:
 * 
 * Input: sentence1 = "My name is Haley", sentence2 = "My Haley"
 * Output: true
 * Explanation: sentence2 can be turned to sentence1 by inserting "name is" between "My" and "Haley".
 * Example 2:
 * 
 * Input: sentence1 = "of", sentence2 = "A lot of words"
 * Output: false
 * Explanation: No single sentence can be inserted inside one of the sentences to make it equal to the other.
 * Example 3:
 * 
 * Input: sentence1 = "Eating right now", sentence2 = "Eating"
 * Output: true
 * Explanation: sentence2 can be turned to sentence1 by inserting "right now" at the end of the sentence.
 *  
 * 
 * Constraints:
 * 
 * 1 <= sentence1.length, sentence2.length <= 100
 * sentence1 and sentence2 consist of lowercase and uppercase English letters and spaces.
 * The words in sentence1 and sentence2 are separated by a single space.
 * 
 */

#include <string>
#include <vector>
#include <sstream>
using namespace std;

class Solution {
public:
    bool areSentencesSimilar(string sentence1, string sentence2) {
        // 分割单词
        vector<string> words1 = split(sentence1);
        vector<string> words2 = split(sentence2);
        
        // 确保 words1 是较短的句子
        if (words1.size() > words2.size()) {
            swap(words1, words2);
        }
        
        int len1 = words1.size();
        int len2 = words2.size();
        int i = 0, j = 0;
        
        // 从开头匹配
        while (i < len1 && words1[i] == words2[i]) {
            ++i;
        }
        
        // 从结尾匹配，只匹配短句中尚未被前缀覆盖的部分
        while (j < len1 - i && words1[len1 - 1 - j] == words2[len2 - 1 - j]) {
            ++j;
        }
        
        // 如果前缀和后缀覆盖了整个短句，则相似
        return i + j >= len1;
    }

private:
    vector<string> split(const string& s) {
        vector<string> res;
        istringstream iss(s);
        string word;
        while (iss >> word) {
            res.push_back(word);
        }
        return res;
    }
};