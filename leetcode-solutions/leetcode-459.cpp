/*
 * Repeated Substring Pattern
 *
 * Given a string s, check if it can be constructed by taking a substring of it and appending multiple copies of the substring together.
 *
 * Constraints:
 * 1 <= s.length <= 104
 * s consists of lowercase English letters.
 * 
 */
#include <string>
using namespace std;

bool repeatedSubstringPattern(string s) { return (s + s).substr(1, 2 * s.size() - 2).find(s) != string::npos; }