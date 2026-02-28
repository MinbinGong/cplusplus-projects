/*
 * 1233. Remove Sub-Folders from the Filesystem
 *
 * Given a list of folders, remove all sub-folders in those folders and return in any order the folders after removing.
 *
 * If a folder[i] is located within another folder[j], it is called a sub-folder of it.
 *
 * The format of a path is one or more concatenated strings of the form: / followed by one or more lowercase English letters. For example, /leetcode and /leetcode/problems are valid paths while an empty string and / are not.
 *
 * Example 1:
 * 
 * Input: folders = ["/a","/a/b","/c/d","/c/d/e","/c/f"]
 * Output: ["/a","/c/d","/c/f"]
 * Explanation: Folders "/a/b/" is a subfolder of "/a" and "/c/d/e" is inside of folder "/c/d" in our filesystem.
 * 
 * Example 2:
 * 
 * Input: folders = ["/a","/a/b/c","/a/b/d"]
 * Output: ["/a"]
 * Explanation: Folders "/a/b/c" and "/a/b/d/" will be removed because they are subfolders of "/a".
 * 
 * Example 3:
 * 
 * Input: folders = ["/a/b/c","/a/b/ca","/a/b/d"]
 * Output: ["/a/b/c","/a/b/ca","/a/b/d"]
 * 
 * Note:
 * 1 <= folders.length <= 4 * 10^4
 * 2 <= folders[i].length <= 100
 * folders[i] contains only lowercase letters and '/'
 * folders[i] always starts with character '/'
 * Each folder name is unique.
 * 
 */
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <iostream>
using namespace std;

class Solution1 {
public:
    vector<string> removeSubfolders(vector<string>& folder) {
        // 1. 按字典序排序
        sort(folder.begin(), folder.end());
        
        vector<string> result;
        
        // 2. 遍历文件夹列表
        for (const string& f : folder) {
            // 如果结果为空，直接添加第一个文件夹
            if (result.empty()) {
                result.push_back(f);
                continue;
            }
            
            // 获取结果中最后一个文件夹（当前可能的父文件夹）
            const string& last = result.back();
            
            // 3. 检查当前文件夹是否是最后一个文件夹的子文件夹
            // 条件：当前文件夹以父文件夹路径开头，并且下一个字符是'/'
            // 或者父文件夹路径就是当前文件夹（完全相同的情况）
            if (f.size() > last.size() && 
                f.compare(0, last.size(), last) == 0 && 
                f[last.size()] == '/') {
                // 是子文件夹，跳过
                continue;
            }
            
            // 不是子文件夹，添加到结果中
            result.push_back(f);
        }
        
        return result;
    }
};

// 方法2：使用前缀树（Trie）的解法
class TrieNode {
public:
    unordered_map<string, TrieNode*> children;
    bool isEnd;  // 标记是否为文件夹路径的终点
    
    TrieNode() : isEnd(false) {}
};

class Solution2 {
public:
    vector<string> removeSubfolders(vector<string>& folder) {
        // 构建前缀树
        TrieNode* root = new TrieNode();
        
        // 插入所有文件夹路径
        for (const string& path : folder) {
            insert(root, path);
        }
        
        vector<string> result;
        
        // 遍历所有文件夹，检查是否是子文件夹
        for (const string& path : folder) {
            if (!isSubfolder(root, path)) {
                result.push_back(path);
            }
        }
        
        // 清理内存（实际面试中可能不需要）
        deleteTrie(root);
        
        return result;
    }
    
private:
    void insert(TrieNode* root, const string& path) {
        TrieNode* node = root;
        stringstream ss(path);
        string segment;
        
        while (getline(ss, segment, '/')) {
            if (segment.empty()) continue;  // 跳过开头的空字符串
            
            if (node->children.find(segment) == node->children.end()) {
                node->children[segment] = new TrieNode();
            }
            node = node->children[segment];
        }
        node->isEnd = true;
    }
    
    bool isSubfolder(TrieNode* root, const string& path) {
        TrieNode* node = root;
        stringstream ss(path);
        string segment;
        
        while (getline(ss, segment, '/')) {
            if (segment.empty()) continue;
            
            if (node->children.find(segment) == node->children.end()) {
                return false;
            }
            node = node->children[segment];
            
            // 如果在路径中间遇到一个文件夹终点，说明是子文件夹
            if (node->isEnd && !ss.eof()) {
                return true;
            }
        }
        return false;
    }
    
    void deleteTrie(TrieNode* node) {
        if (!node) return;
        for (auto& child : node->children) {
            deleteTrie(child.second);
        }
        delete node;
    }
};

// 方法3：更简洁的排序解法
class Solution3 {
public:
    vector<string> removeSubfolders(vector<string>& folder) {
        sort(folder.begin(), folder.end());
        
        vector<string> result = {folder[0]};
        
        for (int i = 1; i < folder.size(); ++i) {
            string last = result.back();
            last.push_back('/');  // 添加'/'确保完全匹配父文件夹
            
            // 检查当前文件夹是否以"父文件夹/"开头
            if (folder[i].compare(0, last.size(), last) != 0) {
                result.push_back(folder[i]);
            }
        }
        
        return result;
    }
};

// 测试用例示例：
// 输入: folder = ["/a","/a/b","/c/d","/c/d/e","/c/f"]
// 输出: ["/a","/c/d","/c/f"]
// 解释: "/a/b" 是 "/a" 的子文件夹，"/c/d/e" 是 "/c/d" 的子文件夹
//
// 输入: folder = ["/a","/a/b/c","/a/b/d"]
// 输出: ["/a"]
// 解释: "/a/b/c" 和 "/a/b/d" 都是 "/a" 的子文件夹
//
// 输入: folder = ["/a/b/c","/a/b/ca","/a/b/d"]
// 输出: ["/a/b/c","/a/b/ca","/a/b/d"]
// 解释: "/a/b/ca" 不是 "/a/b/c" 的子文件夹，因为'c'后面没有'/'

// 复杂度分析：
// 排序解法：
// - 时间复杂度：O(n * m * log n)，其中n是文件夹数量，m是平均路径长度
// - 空间复杂度：O(1) 或 O(n)（取决于排序实现）
//
// Trie解法：
// - 时间复杂度：O(n * m)，其中n是文件夹数量，m是平均路径长度
// - 空间复杂度：O(n * m)，用于存储Trie节点