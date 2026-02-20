/*
 * Unique Word Abbreviation
 * 
 * An abbreviation of a word follows the form <first letter><number><last letter>.
 * Below are some examples of word abbreviations:
 * a) it does not have any meaning.
 * b) it is ambiguous.
 * 
 * For example:
 * 
 * a) "dear" -> "d2r" (abbreviation of "dear")
 * b) "door" -> "d2r" (abbreviation of "door")
 * 
 * Given a dictionary and a word, find whether its abbreviation is unique in the dictionary.
 * A word's abbreviation is unique if no other word from the dictionary has the same abbreviation.
 * 
 * Example:
 * 
 * Given dictionary = [ "deer", "door", "cake", "card" ]
 * 
 * isUnique("dear") -> false
 * isUnique("cart") -> true
 * isUnique("cane") -> false
 * isUnique("make") -> true
 * 
 */
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class ValidWordAbbr {
private:
    unordered_map<string, unordered_set<string>> abbrDict; // 缩写 -> 单词集合

    // 计算单词的缩写
    string getAbbreviation(const string& word) {
        int n = word.length();
        if (n <= 2) {
            return word;
        }
        // 首字母 + 中间字母个数 + 尾字母
        return word[0] + to_string(n - 2) + word.back();
    }

public:
    ValidWordAbbr(vector<string>& dictionary) {
        for (const string& word : dictionary) {
            string abbr = getAbbreviation(word);
            abbrDict[abbr].insert(word);
        }
    }

    bool isUnique(string word) {
        string abbr = getAbbreviation(word);
        // 情况1：缩写不存在于字典中
        if (abbrDict.find(abbr) == abbrDict.end()) {
            return true;
        }
        // 情况2：缩写存在，但集合中只有当前单词（包括单词本身）
        const auto& words = abbrDict[abbr];
        return words.size() == 1 && words.count(word) > 0;
    }
};

/**
 * Your ValidWordAbbr object will be instantiated and called as such:
 * ValidWordAbbr* obj = new ValidWordAbbr(dictionary);
 * bool param_1 = obj->isUnique(word);
 */