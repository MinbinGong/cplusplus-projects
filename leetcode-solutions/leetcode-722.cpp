/*
 * Remove Comments
 * 
 * Given a C++ program, remove comments from it. The program source is an array where source[i] is the i-th line of the source code. This represents the result of splitting the original source code string by the newline character \n.
 * 
 * Note:
 * 1. The length of source is in the range [1, 100].
 * 2. The length of source[i] is in the range [0, 80].
 * 3. Every open block comment is eventually closed.
 * 4. There are no single-quote or double-quote in the input.
 * 
 */
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    vector<string> removeComments(vector<string>& source) {
        vector<string> result;
        bool inBlock = false;          // are we inside a block comment?
        string newLine;                 // current output line being built

        for (const string& line : source) {
            int n = line.size();
            int i = 0;

            while (i < n) {
                if (inBlock) {
                    // inside block comment: look for "*/"
                    if (i + 1 < n && line[i] == '*' && line[i + 1] == '/') {
                        inBlock = false;    // end of block comment
                        i += 2;
                    } else {
                        ++i;                // skip everything inside block
                    }
                } else {
                    // not inside any comment
                    if (i + 1 < n && line[i] == '/' && line[i + 1] == '/') {
                        // line comment: ignore rest of the line
                        break;
                    } else if (i + 1 < n && line[i] == '/' && line[i + 1] == '*') {
                        // start of block comment
                        inBlock = true;
                        i += 2;
                    } else {
                        // normal character, add to output
                        newLine.push_back(line[i]);
                        ++i;
                    }
                }
            }

            // after finishing the line, if we are not inside a block comment
            // and the current output line is non‑empty, save it
            if (!inBlock && !newLine.empty()) {
                result.push_back(newLine);
                newLine.clear();
            }
        }

        return result;
    }
};