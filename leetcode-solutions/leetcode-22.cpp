/*
 * Generate Parentheses
 * Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses
 * 
 * Example 1:
 * Input: n = 3
 * Output: ["((()))","(()())","(())()","()(())","()()()"]
 * 
 * Example 2:
 * Input: n = 1
 * Output: ["()"]
 * 
 * Note:
 * Each tree has at most 5000 nodes.
 * Each node's value is between [-10^5, 10^5].
 * 
 */
#include <string>
#include <vector>
using namespace std;

void solve(vector<string>& ans, int open, int close, string output) {
  if (open == 0 && close == 0) {
    ans.push_back(output);
    return;
  }

  if (open > 0) {
    solve(ans, open - 1, close, output + "(");
  }

  if (close > 0) {
    solve(ans, open, close - 1, output + ')');
  }
}

vector<string> generateParenthesis(int n) {
  vector<string> ans;
  int open = 0, close = n;
  string output{""};
  solve(ans, open, close, output);
  return ans;
}