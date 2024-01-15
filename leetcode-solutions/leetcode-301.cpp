/*
 * 301. Remove Invalid Parentheses
 * Remove the minimum number of invalid parentheses in order to make the input string valid. Return all possible
 * results. Note: The input string may contain letters other than the parentheses ( and ).
 */

#include <queue>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

bool isValid(std::string &str) {
  int cnt{0};
  for (int i = 0; i < str.length(); ++i) {
    if (str[i] == '(') {
      ++cnt;
    } else if (str[i] == ')') {
      --cnt;
    }

    if (cnt < 0) {
      return false;
    }
  }

  return (cnt == 0);
}

std::pair<int, int> bracketsToRemove(std::string &str) {
  int open{0}, close{0}, openToRemove{0}, closeToRemove{0};

  for (int i = 0; i < str.length(); i++) {
    if (str[i] == '(') {
      ++open;
    } else if (str[i] == ')') {
      ++close;
    }

    if (close > open) {
      closeToRemove += close - open;
      close = open;
    }
  }

  if (open > close) {
    openToRemove += open - close;
  }

  return {openToRemove, closeToRemove};
}

std::vector<std::string> removeInvalidParentheses(std::string &str) {
  auto toRemove = bracketsToRemove(str);

  if (toRemove.first == 0 && toRemove.second == 0) {
    return {str};
  }

  std::vector<std::string> res;

  std::unordered_set<std::string> visited;
  std::queue<std::string> Q;
  Q.push(str);

  while (!Q.empty()) {
    int szQueue = Q.size();
    while (szQueue--) {
      auto u = Q.front();
      Q.pop();
      if (toRemove.first == 0 && toRemove.second == 0) {
        if (isValid(u)) {
          res.push_back(u);
        }
        continue;
      }

      for (int i = 0; i < u.size(); ++i) {
        if (toRemove.first > 0) {
          if (u[i] == '(') {
            std::string tmp = u.substr(0, i) + u.substr(i + 1);
            if (visited.find(tmp) == visited.end()) {
              Q.push(tmp);
              visited.insert(tmp);
            }
          } else {
            if (u[i] == ')') {
              std::string tmp = u.substr(0, i) + u.substr(i + 1);
              if (visited.find(tmp) == visited.end()) {
                Q.push(tmp);
                visited.insert(tmp);
              }
            }
          }
        }
      }

      if (toRemove.first > 0) {
        toRemove.first -= 1;
      } else {
        toRemove.second -= 1;
      }
    }

    return res;
  }