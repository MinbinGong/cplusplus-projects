/**
 * 1410. HTML Entity Parser
 * 
 * HTML entity parser is the parser that takes HTML code as input and replace all the entities of the special characters by the characters itself.
 * The special characters and their entities for HTML are:
 * Quotation Mark: the entity is &quot; and symbol character is ".
 * Single Quote Mark: the entity is &apos; and symbol character is '.
 * Ampersand: the entity is &amp; and symbol character is &.
 * Greater Than Sign: the entity is &gt; and symbol character is >.
 * Less Than Sign: the entity is &lt; and symbol character is <.
 * Slash: the entity is &frasl; and symbol character is /.
 * Given the input text string to the HTML parser, you have to implement the entity parser.
 * Return the text after replacing the entities by the special characters.
 * 
 * Example 1:
 * Input: text = "&amp; is an HTML entity but &ambassador; is not."
 * Output: "& is an HTML entity but &ambassador; is not."
 * Explanation: The parser will replace the &amp; entity by &
 * 
 * Example 2:
 * Input: text = "and I quote: &quot;...&quot;"
 * Output: "and I quote: \"...\""
 * Explanation: The parser will replace the &quot; entity by "
 * 
 * Note:
 * The entities must be replaced in the order they appear in the text.
 * The text length may be very large so you should implement an efficient solution.
 * 
 */
#include <string>
#include <unordered_map>
using namespace std;

class Solution {
public:
    string entityParser(string text) {
        // Map each entity string to its corresponding character
        unordered_map<string, char> entities = {
            {"&quot;", '"'},
            {"&apos;", '\''},
            {"&amp;", '&'},
            {"&gt;", '>'},
            {"&lt;", '<'},
            {"&frasl;", '/'}
        };

        string result;
        int n = text.size();

        for (int i = 0; i < n; ) {
            if (text[i] != '&') {
                // Normal character, just append
                result.push_back(text[i]);
                ++i;
            } else {
                // Try to find the closing ';'
                int j = i + 1;
                while (j < n && text[j] != ';') {
                    ++j;
                }

                if (j == n) {
                    // No ';' found – treat '&' as literal
                    result.push_back('&');
                    ++i;
                } else {
                    // Extract the candidate entity substring
                    string candidate = text.substr(i, j - i + 1);
                    auto it = entities.find(candidate);
                    if (it != entities.end()) {
                        // Valid entity: replace with its character
                        result.push_back(it->second);
                        i = j + 1;          // skip the whole entity
                    } else {
                        // Not a known entity: keep the '&' and move on
                        result.push_back('&');
                        ++i;
                    }
                }
            }
        }
        return result;
    }
};