/*
 * Sentence Similarity
 *
 * Given two sentences words1, words2 (each represented as an array of strings), and a list of similar word pairs pairs, determine if two sentences are similar.
 * 
 * For example, words1 = ["great", "acting", "skills"] and words2 = ["fine", "drama", "talent"] are similar, if the similar word pairs are pairs = [["great", "good"], ["fine", "good"], ["acting","drama"], ["skills","talent"]].
 * 
 * Note that the similarity relation is transitive. For example, if "great" and "good" are similar, and "fine" and "good" are similar, then "great" and "fine" are similar.
 * 
 * Similarity is also symmetric. For example, "great" and "fine" being similar is the same as "fine" and "great" being similar.
 * 
 * Also, a word is always similar with itself. For example, the sentences words1 = ["great"], words2 = ["great"], pairs = [] are similar, even though there are no specified similar word pairs.
 * 
 * Note:
 * 1. The length of words1 and words2 will not exceed 1000.
 * 2. The length of pairs will not exceed 2000.
 * 3. The length of each pairs[i] will be 2.
 * 4. The length of each words[i] and pairs[i][j] will be in the range [1, 20].
 * 
 */
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class Solution {
public:
    bool areSentencesSimilar(vector<string>& sentence1, vector<string>& sentence2, vector<vector<string>>& similarPairs) {
        // 长度必须相同 [citation:3][citation:4]
        if (sentence1.size() != sentence2.size()) {
            return false;
        }
        
        // 构建相似关系映射表（双向存储） [citation:1][citation:5]
        unordered_map<string, unordered_set<string>> simMap;
        for (const auto& pair : similarPairs) {
            simMap[pair[0]].insert(pair[1]);
            simMap[pair[1]].insert(pair[0]);
        }
        
        // 逐词比较 [citation:4]
        for (int i = 0; i < sentence1.size(); ++i) {
            const string& word1 = sentence1[i];
            const string& word2 = sentence2[i];
            
            // 相同则自动相似 [citation:3]
            if (word1 == word2) {
                continue;
            }
            
            // 检查相似关系（双向已存，只需查一次） [citation:1]
            if (simMap.find(word1) == simMap.end() || 
                simMap[word1].find(word2) == simMap[word1].end()) {
                return false;
            }
        }
        
        return true;
    }
};