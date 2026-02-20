/*
 * Encode and Decode Strings
 *
 * Design an algorithm to encode a list of strings to a string. The encoded string is then sent over the network and is decoded back to the original list of strings.
 *
 * Please implement encode and decode
 * 
 * Constraints:
 * 1. 1 <= strs.length <= 200
 * 2. 0 <= strs[i].length <= 200
 * 3. strs[i] contains any possible characters out of 256 valid ASCII characters.
 * 4. Do not use class member/global/static variables to store states. Your encode and decode algorithms should be stateless.
 * 5. The encoded string must be as short as possible.
 * 6. The decoded list of strings must be the same as the original list of strings.
 * 
 */
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

// 时间复杂度：O(n)
// 空间复杂度：O(n)
class Codec1 {
private:
    const char HEX[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
    
    // 整数转4位十六进制字符串
    string int2Hex(int n) {
        string res;
        while (n > 0) {
            res += HEX[n % 16];
            n /= 16;
        }
        // 补齐4位
        if (res.size() < 4) {
            res.append(4 - res.size(), '0');
        }
        reverse(res.begin(), res.end());
        return res;
    }
    
    // 4位十六进制字符串转整数
    int hex2Int(const string& s) {
        int res = 0;
        for (char c : s) {
            res <<= 4; // 左移4位腾出空间
            if (c <= '9')
                res |= (c - '0');
            else
                res |= (c - 'A' + 10);
        }
        return res;
    }
    
public:
    // 编码
    string encode(vector<string>& strs) {
        string res;
        for (auto& s : strs) {
            res += int2Hex(s.size());  // 加4字节长度头
            res += s;                   // 加字符串内容
        }
        return res;
    }

    // 解码
    vector<string> decode(string s) {
        vector<string> res;
        int i = 0;
        int N = s.size();
        while (i < N) {
            // 读取长度头（4字节）
            int len = hex2Int(s.substr(i, 4));
            i += 4;
            // 读取字符串内容
            res.push_back(s.substr(i, len));
            i += len;
        }
        return res;
    }
};

// 时间复杂度：O(n)
// 空间复杂度：O(n)
class Codec2 {
public:
    // 编码
    string encode(vector<string>& strs) {
        string res;
        for (const string& s : strs) {
            res += to_string(s.length()) + "#" + s;
        }
        return res;
    }

    // 解码
    vector<string> decode(string s) {
        vector<string> res;
        int i = 0;
        while (i < s.length()) {
            // 找到 '#' 的位置
            int j = i;
            while (s[j] != '#') j++;
            
            // 解析长度
            int len = stoi(s.substr(i, j - i));
            
            // 提取字符串
            res.push_back(s.substr(j + 1, len));
            
            // 移动到下一个单元
            i = j + 1 + len;
        }
        return res;
    }
};