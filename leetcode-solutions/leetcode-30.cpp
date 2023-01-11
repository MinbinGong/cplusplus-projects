// Leetcode 30,  Substring with Concatenation of All Words

// Approach : We are using Hashing & Sliding Window Technique to solve the above problem.
// 1.Declare a map wordCount which stores all words count
// 2.Select a window of size wordsWindow(total number of characters produced if all the words are concatenated)
// 3.Check if that window is possible to build using our wordCount map.
// 4.If True, add the starting index to our result vector
// 5.Increasing the window by 1 & check until we are able to select wordsWindow size window.
//

#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

bool checkSubstring(unordered_map<string, int> wordCount, string s, int wordLen)
{
    for (int j = 0; j < s.size(); j += wordLen)
    {
        string w = s.substr(j, wordLen);
        if (wordCount.find(w) != wordCount.end())
        {
            if (--wordCount[w] == -1)
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    return true;
}

std::vector<int> find_substring(std::string s, std::vector<std::string> &words)
{
    vector<int> res;
    int wordLen = words[0].size();
    int sLen = s.size();
    int wordsWindow = words.size() * wordLen;

    unordered_map<string, int> wordCount;
    for (int i = 0; i < words.size(); i++)
    {
        wordCount[words[i]]++;
    }

    int i = 0;
    while (i + wordsWindow <= sLen)
    {
        if (checkSubstring(wordCount, s.substr(i, wordsWindow), wordLen))
        {
            res.push_back(i);
        }
        i++;
    }
    return res;
}