/*
 * Strobogrammatic Number 
 * 
 * A strobogrammatic number is a number that looks the same when rotated 180 degrees (looked at upside down).
 * 
 * Write a function to determine if a number is strobogrammatic. The number is represented as a string.
 * 
 * Constraints:
 * 1. 1 <= num.length <= 50
 * 2. num consists of only digits.
 * 3. num does not contain any leading zeros except for zero itself.
 */
#include <string>
#include <unordered_map>
using namespace std;

class Solution {
public:
    bool isStrobogrammatic(string num) {
        unordered_map<char, char> map = {
            {'0', '0'},
            {'1', '1'},
            {'6', '9'},
            {'8', '8'},
            {'9', '6'}
        };
        
        int left = 0;
        int right = num.size() - 1;
        
        while (left <= right) {
            char c = num[left];
            // If left char is not in map, or its mapping doesn't match right char, return false
            if (map.find(c) == map.end() || map[c] != num[right]) {
                return false;
            }
            left++;
            right--;
        }
        return true;
    }
};