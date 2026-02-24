/*
 * 831. Masking Personal Information
 * 
 * We are given a personal information string S, which may represent either an email address or a phone number.
 * We would like to mask this personal information according to the following rules:
 * 
 * 1. Email address:
 * We define a name to be a string of length ≥ 2 consisting of only lowercase letters a-z or uppercase letters A-Z.
 * An email address starts with a name, followed by the symbol '@', followed by a name, followed by the dot '.' and followed by a name.
 * All email addresses are guaranteed to be valid and in the format of 'name1@name2.name3'.
 * To mask an email, all names must be converted to lowercase and all letters between the first and last letter of the first name must be replaced by 5 asterisks '*'.
 * 
 * 2. Phone number:
 * A phone number is a string consisting of only the digits 0-9 or the characters from the set {'+', '-', '(', ')', ' '}. You may assume a phone number contains 10 to 13 digits.
 * The last 10 digits make up the local number, while the digits before those make up the country code. Note that the country code is optional. We want to expose only the last 4 digits and mask all other digits.
 * The local number should be formatted and masked as "***-***-1111", where 1 represents the exposed digits.
 * 
 * Example:
 * Input: "LeetCode@LeetCode.com"
 * Output: "l*****e@leetcode.com"
 * 
 * Input: "AB@qq.com"
 * Output: "a*****b@qq.com"
 * 
 * Input: "1(234)567-890"
 * Output: "***-***-7890"
 * 
 * Input: "86-(10)12345678"
 * Output: "+**-***-***-5678"
 * 
 * Note:
 * 1 <= S.length <= 40
 * S is a valid email or phone number.
 * S contains only lowercase letters a-z, uppercase letters A-Z, digits 0-9, characters '+', '-', '(', ')', and ' '.
 * 
 */
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Solution {
public:
    string maskPII(string s) {
        // Check if it's an email (contains '@')
        size_t at_pos = s.find('@');
        if (at_pos != string::npos) {
            // Email
            string name = s.substr(0, at_pos);
            string domain = s.substr(at_pos + 1);
            // Convert to lowercase
            transform(name.begin(), name.end(), name.begin(), ::tolower);
            transform(domain.begin(), domain.end(), domain.begin(), ::tolower);
            // Mask name: first letter + "*****" + last letter
            string masked = name.substr(0, 1) + "*****" + name.substr(name.size() - 1);
            return masked + "@" + domain;
        } else {
            // Phone number: extract all digits
            string digits;
            for (char c : s) {
                if (isdigit(c)) digits += c;
            }
            int n = digits.size();
            string last4 = digits.substr(n - 4);
            string local = "***-***-" + last4;
            // If no country code (10 digits), just local part
            if (n == 10) return local;
            // Otherwise, add country code prefix
            string country = digits.substr(0, n - 10);
            return "+" + string(country.size(), '*') + "-" + local;
        }
    }
};