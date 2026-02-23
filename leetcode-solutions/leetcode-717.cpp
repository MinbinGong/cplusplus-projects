/*
 * 1-bit and 2-bit Characters
 *
 * We have two special characters:
 * 
 * The first character can be represented by one bit 0.
 * The second character can be represented by two bits (10 or 11).
 * 
 * Given a binary array bits that ends with 0, return true if the last character must be a one-bit character.
 * 
 * Example 1:
 * 
 * Input: bits = [1,0,0]
 * Output: true
 * Explanation: The only way to decode it is two-bit character and one-bit character.
 * So the last character is one-bit character.
 * 
 * Example 2:
 * 
 * Input: bits = [1,1,1,0]
 * Output: false
 * Explanation: The only way to decode it is two-bit character and two-bit character.
 * So the last character is not one-bit character.
 * 
 * Note:
 * 
 * 1 <= bits.length <= 1000.
 * bits[i] is either 0 or 1.
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    bool isOneBitCharacter(vector<int>& bits) {
        int n = bits.size();
        int i = 0;
        while (i < n - 1) { // stop before the last bit
            if (bits[i] == 0) {
                // 1-bit character (0)
                i += 1;
            } else {
                // 2-bit character (10 or 11)
                i += 2;
            }
        }
        // If we ended exactly at the last index, it's a 1-bit character
        return i == n - 1;
    }
};