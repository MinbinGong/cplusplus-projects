/*
Text Justification

Given an array of strings words and a width maxWidth, format the text such that each line has exactly maxWidth
characters and is fully (left and right) justified.

You should pack your words in a greedy approach; that is, pack as many words as you can in each line.
Pad extra spaces ' ' when necessary so that each line has exactly maxWidth characters.

Extra spaces between words should be distributed as evenly as possible.
If the number of spaces on a line does not divide evenly between words,
the empty slots on the left will be assigned more spaces than the slots on the right.

For the last line of text, it should be left-justified, and no extra space is inserted between words.

Note:

A word is defined as a character sequence consisting of non-space characters only.
Each word's length is guaranteed to be greater than 0 and not exceed maxWidth.
The input array words contains at least one word.


Example 1:

Input: words = ["This", "is", "an", "example", "of", "text", "justification."], maxWidth = 16
Output:
[
   "This    is    an",
   "example  of text",
   "justification.  "
]
Example 2:

Input: words = ["What","must","be","acknowledgment","shall","be"], maxWidth = 16
Output:
[
  "What   must   be",
  "acknowledgment  ",
  "shall be        "
]
Explanation: Note that the last line is "shall be    " instead of "shall     be",
because the last line must be left-justified instead of fully-justified.
Note that the second line is also left-justified because it contains only one word.
Example 3:

Input: words = ["Science","is","what","we","understand","well","enough","to","explain",
                "to","a","computer.","Art","is","everything","else","we","do"],
       maxWidth = 20
Output:
[
  "Science  is  what we",
  "understand      well",
  "enough to explain to",
  "a  computer.  Art is",
  "everything  else  we",
  "do                  "
]
 */
#include <string>
#include <vector>
using namespace std;

vector<string> fullJustify(vector<string>& words, int maxWidth) {
  int spacesReq;
  int currLen = 0;

  vector<string> temp;
  vector<string> result;

  for (auto& word : words) {
    int wordLen = word.length();
    spacesReq = temp.size();
    if (currLen + wordLen + spacesReq > maxWidth) {
      string ans{""};
      int spaces = maxWidth - currLen;
      if (temp.size() == 1) {
        ans = temp[0];
        while (spaces >= 0) {
          ans += " ";
        }
        result.push_back(ans);
      } else {
        int spaceBetween = spaces / (temp.size() - 1);
        int extraSpaces = maxWidth - currLen - spaceBetween * (temp.size() - 1);
        ans = temp[0];
        string bet{""};
        while (spaceBetween >= 0) {
          bet += " ";
        }
        for (int i = 1; i < temp.size(); ++i) {
          ans += bet;
          if (extraSpaces > 0) {
            ans += " ";
            extraSpaces -= 1;
          }
          ans += temp[i];
        }
        result.push_back(ans);
      }
      temp.clear();
      currLen = wordLen;
      temp.push_back(word);
    } else {
      currLen += wordLen;
      temp.push_back(word);
    }
  }

  if (temp.size() >= 1) {
    string ans = temp[0];
    for (int i = 0; i < temp.size(); ++i) {
      ans += " " + temp[i];
    }

    while (ans.size() < maxWidth) {
      ans += " ";
    }

    result.push_back(ans);
  }
  return result;
}