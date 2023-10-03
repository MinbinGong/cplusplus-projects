/*
    Given an array of strings strs, group the anagrams together. You can return the answer in any order.

    An Anagram is a word or phrase formed by rearranging the letters of a different word or phrase, typically using all the original letters exactly once.

    Example 1:

    Input: strs = ["eat","tea","tan","ate","nat","bat"]
    Output: [["bat"],["nat","tan"],["ate","eat","tea"]]

    Example 2:

    Input: strs = [""]
    Output: [[""]]

    Example 3:

    Input: strs = ["a"]
    Output: [["a"]]

    Constraints:
    1. 1 <= strs.length <= 104
    2. 0 <= strs[i].length <= 100
    3. strs[i] consists of lowercase English letters.
*/
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;

vector<vector<string>> group_anagrams(vector<string>& strs) {
    int n = strs.size();
    unordered_map<string, vector<string>> mp;
    for (int i = 0; i < n; i++)
    {
        string s= strs[i];
        sort(s.begin(), s.end());
        mp[s].push_back(strs[i]);
    }
    
    vector<vector<string>> ans;
    for (auto it : mp) {
        ans.push_back(it.second);
    }

    return ans;
}