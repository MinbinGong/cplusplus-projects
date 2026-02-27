/*
 * 1108. Defanging an IP Address
 * 
 * Given a valid (IPv4) IP address, return a defanged version of that IP address.
 * 
 * A defanged IP address replaces every period "." with "[.]".
 * 
 * 1 <= address.length <= 30
 * address is a valid IPv4 address.
 * 
 */
#include <string>
#include <regex>

using namespace std;

class Solution1 {
public:
    string defangIPaddr(string address) {
        string result;
        
        // 方法1：遍历并替换
        for (char c : address) {
            if (c == '.') {
                result += "[.]";
            } else {
                result += c;
            }
        }
        
        return result;
    }
};

class Solution2 {
public:
    string defangIPaddr(string address) {
        stringstream ss;
        for (char c : address) {
            if (c == '.') {
                ss << "[.]";
            } else {
                ss << c;
            }
        }
        return ss.str();
    }
};

class Solution3 {
public:
    string defangIPaddr(string address) {
        return regex_replace(address, regex("\\."), "[.]");
    }
};

class Solution4 {
public:
    string defangIPaddr(string address) {
        string result = address;
        size_t pos = 0;
        while ((pos = result.find('.', pos)) != string::npos) {
            result.replace(pos, 1, "[.]");
            pos += 3; // 跳过新插入的字符
        }
        return result;
    }
};