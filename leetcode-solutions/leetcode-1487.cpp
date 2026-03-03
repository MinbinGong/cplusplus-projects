/**
 * 1487. Making File Names Unique
 * 
 * Given an array of strings names of size n. You will create n folders in your file system such that, at the ith minute, you will create a folder with the name names[i].
 * 
 * Since two files cannot have the same name, if you enter a folder name which is previously used, the system will have a suffix addition to its name in the form of (k), where, k is the smallest positive integer such that the obtained name remains unique.
 * 
 * Return an array of strings of length n where ans[i] is the actual name the system will assign to the ith folder when you create it.
 * 
 * Example 1:
 * Input: names = ["pes","fifa","gta","pes(2019)"]
 * Output: ["pes","fifa","gta","pes(2019)"]
 * Explanation: Let's see how the file system creates folder names:
 * "pes" --> not assigned before, remains "pes"
 * "fifa" --> not assigned before, remains "fifa"
 * "gta" --> not assigned before, remains "gta"
 * "pes(2019)" --> not assigned before, remains "pes(2019)"
 * 
 * Example 2:
 * Input: names = ["gta","gta(1)","gta","avalon"]
 * Output: ["gta","gta(1)","gta(2)","avalon"]
 * Explanation: Let's see how the file system creates folder names:
 * "gta" --> not assigned before, remains "gta"
 * "gta(1)" --> not assigned before, remains "gta(1)"
 * "gta" --> the name is reserved, system adds (k), since "gta(1)" is also reserved, systems put k = 2. it becomes "gta(2)"
 * "avalon" --> not assigned before, remains "avalon"
 * 
 * Constraints:
 * 1 <= names.length <= 5 * 10^4
 * 1 <= names[i].length <= 20
 * names[i] consists of lowercase English letters, digits, and/or round brackets.
 * 
 */
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class Solution {
public:
    vector<string> getFolderNames(vector<string>& names) {
        unordered_map<string, int> nextIdx;   // 记录每个原始名字下一次要尝试的后缀数字
        unordered_set<string> used;            // 记录所有已经使用的文件名
        vector<string> res;
        
        for (const string& name : names) {
            if (used.find(name) == used.end()) {
                // 名字未被使用，直接采用
                used.insert(name);
                res.push_back(name);
            } else {
                // 名字已被使用，需要加后缀
                int k = nextIdx[name];          // 默认值为0
                if (k == 0) k = 1;               // 从1开始尝试
                string newName;
                // 循环找到第一个可用的后缀数字
                while (used.find(newName = name + "(" + to_string(k) + ")") != used.end()) {
                    ++k;
                }
                used.insert(newName);
                res.push_back(newName);
                nextIdx[name] = k + 1;           // 更新下一次尝试的数字
            }
        }
        return res;
    }
};