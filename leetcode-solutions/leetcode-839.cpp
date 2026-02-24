/*
 * 839. Similar String Groups
 * 
 * Two strings X and Y are similar if we can swap two letters (in different positions) of X, so that it equals Y. Also two strings X and Y are similar if they are equal.
 * 
 * For example, "tars" and "rats" are similar (swapping at positions 0 and 2), and "rats" and "arts" are similar, but "star" is not similar to "tars", "rats", or "arts".
 * 
 * Together, these form two connected groups by similarity: {"tars", "rats", "arts"} and {"star"}.  Notice that "tars" and "arts" are in the same group even though they are not similar.  Formally, each group is such that a word is in the group if and only if it is similar to at least one other word in the group.
 * 
 * We are given a list strs of strings where every string in strs is an anagram of every other string in strs. How many groups are there?
 * 
 * Example 1:
 * Input: strs = ["tars","rats","arts","star"]
 * Output: 2
 * 
 * Example 2:
 * Input: strs = ["omv","ovm"]
 * Output: 1
 * 
 * Note:
 * 1 <= strs.length <= 300
 * 1 <= strs[i].length <= 300
 * strs[i] consists of lowercase letters only.
 * All words in strs have the same length and are anagrams of each other.
 * 
 */
#include <vector>
#include <string>

class Solution {
public:
    // 并查集类
    class UnionFind {
    private:
        std::vector<int> parent;
        int count; // 记录连通分量的个数

    public:
        // 构造函数，初始化每个节点的父节点为自己，连通分量个数为 n
        UnionFind(int n) {
            parent.resize(n);
            for (int i = 0; i < n; ++i) {
                parent[i] = i;
            }
            count = n;
        }

        // 查找操作（带路径压缩）
        int find(int x) {
            if (parent[x] != x) {
                parent[x] = find(parent[x]);
            }
            return parent[x];
        }

        // 合并操作
        void unite(int x, int y) {
            int rootX = find(x);
            int rootY = find(y);
            if (rootX != rootY) {
                parent[rootX] = rootY;
                count--; // 合并后，连通分量个数减一
            }
        }

        // 获取连通分量个数
        int getCount() const {
            return count;
        }
    };

    // 判断两个字符串是否相似
    bool areSimilar(const std::string& a, const std::string& b) {
        int diffCount = 0;
        // 用于记录不同字符的位置，最多只需要两个
        int firstDiff = -1, secondDiff = -1; 
        for (int i = 0; i < a.size(); ++i) {
            if (a[i] != b[i]) {
                diffCount++;
                if (diffCount == 1) {
                    firstDiff = i;
                } else if (diffCount == 2) {
                    secondDiff = i;
                } else {
                    // 如果有两个以上的位置不同，肯定不相似
                    return false; 
                }
            }
        }
        // 情况1：完全相同 (diffCount == 0)
        if (diffCount == 0) return true;
        // 情况2：恰好有两个位置不同，且交换后相等
        if (diffCount == 2) {
            return (a[firstDiff] == b[secondDiff] && a[secondDiff] == b[firstDiff]);
        }
        // 情况3：只有一个位置不同 (diffCount == 1)
        return false;
    }

    int numSimilarGroups(std::vector<std::string>& strs) {
        int n = strs.size();
        UnionFind uf(n);

        // 遍历所有字符串对 (i, j)
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                // 如果两个字符串相似，则合并它们所在的集合
                if (areSimilar(strs[i], strs[j])) {
                    uf.unite(i, j);
                }
            }
        }
        // 返回连通分量的个数，即相似字符串组的数量
        return uf.getCount();
    }
};