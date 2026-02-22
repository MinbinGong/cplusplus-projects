/*
 * 527. Word Abbreviation
 *
 * Given an array of n distinct non-empty strings, you need to generate minimal possible abbreviations for every word following rules below.
 * 1. Begin with the first character and then the number of characters abbreviated, which followed by the last character.
 * 2. If there are any conflict, that is more than one words share the same abbreviation, a longer prefix is used instead of only one character.
 * 3. If the abbreviation doesn't make the word shorter, then keep it as original.
 * 
 */
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

class Solution1 {
public:
    vector<string> wordsAbbreviation(vector<string>& words) {
        int n = words.size();
        vector<string> res(n);
        // pre[i] 代表第 i 个单词当前使用的前缀长度
        vector<int> pre(n, 1);
        // 缩写 -> 出现次数的映射
        unordered_map<string, int> countMap;

        // 辅助函数：根据前缀长度生成缩写
        auto getAbbr = [&](const string& s, int prefixLen) {
            int len = s.length();
            // 如果前缀过长或缩写后不会更短，则返回原词
            if (prefixLen >= len - 2) {
                return s;
            }
            return s.substr(0, prefixLen) + to_string(len - prefixLen - 1) + s.back();
        };

        // 初始化：先为所有单词生成缩写（前缀长度为1）
        for (int i = 0; i < n; ++i) {
            res[i] = getAbbr(words[i], pre[i]);
            countMap[res[i]]++;
        }

        // 循环处理，直到所有缩写唯一
        bool unique = false;
        while (!unique) {
            unique = true;
            for (int i = 0; i < n; ++i) {
                // 如果当前单词的缩写仍有冲突
                if (countMap[res[i]] > 1) {
                    // 增加该单词的前缀长度
                    pre[i]++;
                    // 生成新的缩写
                    string newAbbr = getAbbr(words[i], pre[i]);
                    res[i] = newAbbr;
                    countMap[newAbbr]++;
                    // 标记还有冲突，需要再次循环
                    unique = false;
                }
            }
        }
        return res;
    }
};

// 字典树节点定义
class TrieNode {
public:
    TrieNode* next[26];
    int count; // 记录有多少个单词经过此节点（即拥有此前缀）
    TrieNode() : count(0) {
        memset(next, 0, sizeof(next));
    }
};

class Solution2 {
public:
    vector<string> wordsAbbreviation(vector<string>& dict) {
        int n = dict.size();
        unordered_map<string, vector<int>> group; // 缩写 -> 单词索引列表
        vector<string> ans(n);

        // 1. 按初始缩写进行分组
        for (int i = 0; i < n; ++i) {
            string w = dict[i];
            int len = w.length();
            // 生成长度大于2的单词的初始缩写，否则直接用原词作为分组键
            string abbr = (len > 3) ? w[0] + to_string(len - 2) + w.back() : w;
            group[abbr].push_back(i);
        }

        // 2. 处理每个分组
        for (auto& item : group) {
            vector<int>& indices = item.second;
            // 如果组内只有一个单词，它的缩写就是分组键（如果是按原词分组，则保持原词）
            if (indices.size() == 1) {
                int idx = indices[0];
                string w = dict[idx];
                int len = w.length();
                ans[idx] = (len > 3) ? w[0] + to_string(len - 2) + w.back() : w;
                continue;
            }

            // 组内多个单词，需要建 Trie 树来找到最小唯一前缀
            TrieNode* root = new TrieNode();
            // 先将组内所有单词插入 Trie
            for (int idx : indices) {
                TrieNode* cur = root;
                for (char c : dict[idx]) {
                    if (!cur->next[c - 'a']) cur->next[c - 'a'] = new TrieNode();
                    cur = cur->next[c - 'a'];
                    cur->count++; // 重要：经过该节点的单词数加1
                }
            }

            // 为组内每个单词确定最终缩写
            for (int idx : indices) {
                string w = dict[idx];
                TrieNode* cur = root;
                string prefix = "";
                for (int i = 0; i < w.length(); ++i) {
                    char c = w[i];
                    cur = cur->next[c - 'a'];
                    prefix += c;
                    // 如果当前前缀（节点）的 count == 1，说明这是该单词的独有前缀
                    if (cur->count == 1) {
                        int suffixLen = w.length() - i - 1;
                        // 只有当节省的字符数 > 1 时才用缩写形式
                        if (suffixLen > 1) {
                            ans[idx] = prefix + to_string(suffixLen) + w.back();
                        } else {
                            ans[idx] = w; // 否则保留原词
                        }
                        break;
                    }
                }
            }
            // 释放 Trie 内存（在实际竞赛或生产环境中需要注意，此处为简洁省略）
        }
        return ans;
    }
};