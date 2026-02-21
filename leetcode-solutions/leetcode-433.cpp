/*
 * Minimum Genetic Mutation
 *
 * A gene string can be represented by an 8-character long string, with choices from 'A', 'C', 'G', and 'T'.
 * 
 * Starting with a gene string start, we would like to form a gene string end. To do so, we may make a series of gene mutations.
 * 
 * Each mutation is a single character change in the gene string.
 * 
 * For example, "AACCGGTT" --> "AACCGGTA" is a mutation.
 * 
 * There is also a gene bank bank that records all the valid gene mutations. A gene must be in bank to make it a valid gene string.
 * 
 * Given the two gene strings start and end and the gene bank bank, return the minimum number of mutations needed to mutate from start to end. If there is no such a mutation, return -1.
 * 
 * Note that the starting point is assumed to be valid, so it might not be included in the bank.
 * 
 */
#include <queue>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

int minMutation(string start, string end, vector<string> &bank) {
  unordered_set<string> dict;
  unordered_set<string> visited;
  for (const string s : bank) {
    dict.insert(s);
  }

  if (dict.count(end) == 0) {
    return -1;
  }

  vector<string> choices{"A", "C", "G", "T"};
  queue<string> q;
  q.push(start);
  visited.insert(start);
  int count{0};
  while (!q.empty()) {
    int size = q.size();
    for (size_t i = 0; i < size; i++) {
      string str = q.front();
      q.pop();
      if (str == end) {
        return count;
      }

      for (size_t j = 0; j < str.length(); j++) {
        for (string ch : choices) {
          string tmp{str};
          tmp = tmp.replace(j, 1, ch);
          if (visited.count(tmp) == 0 && dict.count(tmp) == 0) {
            q.push(tmp);
            visited.insert(tmp);
          }
        }
      }
    }
    count++;
  }
  return -1;
}