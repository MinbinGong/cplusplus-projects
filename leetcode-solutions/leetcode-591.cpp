/*
 * Tag Validator
 *
 * Given a string representing a code snippet, you need to implement a tag validator to parse the code and return whether it is valid. A code snippet is valid if all the following rules hold:
 * 
 * The code must be wrapped in a valid closed tag. Otherwise, the code is invalid.
 * A closed tag (not necessarily valid) has exactly the following format : <TAG_NAME>TAG_CONTENT</TAG_NAME>. Among them, <TAG_NAME> is the start tag, and </TAG_NAME> is the end tag. The TAG_NAME in start and end tags should be the same. A closed tag is valid if and only if the TAG_NAME and TAG_CONTENT are valid.
 * A valid TAG_NAME only contain upper-case letters, and has length in range [1,9]. Otherwise, the TAG_NAME is invalid.
 * A valid TAG_CONTENT may contain other valid closed tags, cdata and any characters (see note1) EXCEPT unmatched <, unmatched start and end tag, and unmatched or closed tags with invalid TAG_NAME. Otherwise, the TAG_CONTENT is invalid.
 * A CDATA has the following format : <![CDATA[CDATA_CONTENT]]>. The range of CDATA_CONTENT is defined as the characters between <![CDATA[ and the first subsequent ]]>.
 * CDATA_CONTENT may contain any characters. The function of CDATA is to forbid the validator to parse CDATA_CONTENT, so even it has some characters that can be parsed as tag (no matter valid or invalid), you should treat it as regular characters.
 * 
 * Note:
 * For simplicity, you could assume the input code (including the any characters mentioned above) only contain letters, digits, '<','>','/','!','[',']' and ' '.
 * 
 */
#include <vector>
#include <stack>
using namespace std;

class Solution {
public:
    bool isValid(string code) {
        stack<string> stk;                     // Stack to track open tags
        int i = 0, n = code.size();
        
        while (i < n) {
            // Check for CDATA section first
            if (i + 8 < n && code.substr(i, 9) == "<![CDATA[") {
                // CDATA cannot be at root level (must be inside a tag)
                if (i == 0) return false;
                
                int j = i + 9;
                bool foundEnd = false;
                // Find the first "]]>" that closes CDATA
                while (j < n && !foundEnd) {
                    if (j + 2 < n && code.substr(j, 3) == "]]>") {
                        j += 3;
                        foundEnd = true;
                    } else {
                        j++;
                    }
                }
                if (!foundEnd) return false;   // Unterminated CDATA
                i = j;                          // Move past CDATA
            }
            // Check for tags (either <TAG> or </TAG>)
            else if (code[i] == '<') {
                // Last character cannot be '<'
                if (i == n - 1) return false;
                
                bool isEndTag = (code[i + 1] == '/');
                int startPos = isEndTag ? i + 2 : i + 1;  // Position where tag name starts
                int j = startPos;
                
                // Extract tag name until '>'
                while (j < n && code[j] != '>') {
                    // Tag name must be uppercase letters
                    if (!isupper(code[j])) return false;
                    j++;
                }
                if (j == n) return false;      // No closing '>'
                
                int len = j - startPos;
                // Tag name length must be between 1 and 9
                if (len < 1 || len > 9) return false;
                
                string tagName = code.substr(startPos, len);
                i = j + 1;                       // Move past '>'
                
                if (!isEndTag) {
                    // Start tag: push onto stack
                    stk.push(tagName);
                } else {
                    // End tag: must match most recent open tag
                    if (stk.empty() || stk.top() != tagName) return false;
                    stk.pop();
                    
                    // After closing outer tag, no more content allowed
                    if (stk.empty() && i < n) return false;
                }
            }
            // Plain text content
            else {
                // Text must be inside some tag (cannot be at root level)
                if (i == 0) return false;
                i++;
            }
        }
        
        // All tags must be closed
        return stk.empty();
    }
};