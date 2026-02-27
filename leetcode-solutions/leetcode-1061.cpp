/**
 * 1061. Lexicographically Smallest Equivalent String
 * 
 * You are given two strings of the same length s1 and s2 and a string baseStr.
 * 
 * We say s1[i] and s2[i] are equivalent characters.
 * 
 * For example, if s1 = "abc" and s2 = "cde", then we have 'a' == 'c', 'b' == 'd', and 'c' == 'e'.
 * Equivalent characters follow the usual rules of any equivalence relation:
 * 
 * Reflexivity: 'a' == 'a'.
 * Symmetry: 'a' == 'b' implies 'b' == 'a'.
 * Transitivity: 'a' == 'b' and 'b' == 'c' implies 'a' == 'c'.
 * For example, given the equivalency information from s1 = "abc" and s2 = "cde", "acd" and "aab" are equivalent strings of baseStr = "eed", and "aab" is the lexicographically smallest equivalent string of baseStr.
 * 
 * Example 1:
 * Input: s1 = "parker", s2 = "morris", baseStr = "parser"
 * Output: "makkek"
 * Explanation: Based on the equivalency information in s1 and s2, we can group their characters as [m,p], [a,o], [k,r,s], [e,i].
 * The characters in each group are equivalent and sorted in lexicographical order.
 * So the answer is "makkek".
 * 
 * Example 2:
 * Input: s1 = "hello", s2 = "world", baseStr = "hold"
 * Output: "hdld"
 * Explanation: Based on the equivalency information in s1 and s2, we can group their characters as [h,w], [d,e,o], [l,r].
 * So the answer is "hdld".
 * 
 * Example 3:
 * Input: s1 = "leetcode", s2 = "programs", baseStr = "sourcecode"
 * Output: "aauaaaaada"
 * Explanation: Based on the equivalency information in s1 and s2, we can group their characters as [l,r], [a,o], [e,t,c], [d,g,m,s].
 * The characters in each group are equivalent and sorted in lexicographical order.
 * So the answer is "aauaaaaada".
 * 
 * Note:
 * 1 <= s1.length <= 1000
 * 1 <= s2.length <= 1000
 * 1 <= baseStr <= 1000
 * s1.length == s2.length
 * s1, s2, and baseStr consist of lowercase English letters.
 * 
 */ 
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    // 并查集类
    class DSU {
    private:
        vector<int> parent;
    public:
        // 构造函数，初始化每个字母的父节点为自己
        DSU() {
            parent.resize(26);
            for (int i = 0; i < 26; ++i) {
                parent[i] = i;
            }
        }

        // 查找操作（带路径压缩）
        int find(int x) {
            if (parent[x] != x) {
                parent[x] = find(parent[x]);
            }
            return parent[x];
        }

        // 合并操作：始终让字典序较小的字母作为根（父节点）
        void unionSets(int x, int y) {
            int rootX = find(x);
            int rootY = find(y);
            if (rootX == rootY) return;
            
            // 关键点：让较小的字母成为新的根
            if (rootX < rootY) {
                parent[rootY] = rootX;
            } else {
                parent[rootX] = rootY;
            }
        }
    };

    string smallestEquivalentString(string s1, string s2, string baseStr) {
        DSU dsu;
        int n = s1.length();
        
        // 1. 根据 s1 和 s2 的对应关系，合并等价字符
        for (int i = 0; i < n; ++i) {
            dsu.unionSets(s1[i] - 'a', s2[i] - 'a');
        }
        
        // 2. 转换 baseStr 中的每个字符
        for (int i = 0; i < baseStr.length(); ++i) {
            // 找到该字符所在集合的根（即该组的最小字母）
            int minCharIndex = dsu.find(baseStr[i] - 'a');
            baseStr[i] = minCharIndex + 'a';
        }
        
        return baseStr;
    }
};