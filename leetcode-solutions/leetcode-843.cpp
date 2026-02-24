/*
 * 843. Guess the Word
 *
 * This problem is an interactive problem new to the LeetCode platform.
 *
 * We are given a word list of unique words, each word is 6 letters long, and one word in this list is chosen as secret.
 *
 * You may call master.guess(word) to guess a word.  The guessed word should have type string and must be from the
 * original list with 6 lowercase letters.
 *
 * This function returns an integer type, representing the number of exact matches (value and position) of your guess to
 * the secret word.  Also, if your guess is not in the given wordlist, it will return -1 instead.
 *
 * For each test case, you have 10 guesses to guess the word. At the end of any number of calls, if you have made 10 or
 * less calls to master.guess and at least one of these guesses was the secret, you pass the testcase.
 *
 * Besides the example test case below, there will be 5 additional test cases, each with 100 words in the word list. The
 * letters of each word in those testcases were chosen independently at random from 'a' to 'z', such that every word in
 * the given word lists is unique.
 *
 * Example 1:
 * Input: secret = "acckzz", wordlist = ["acckzz","ccbazz","eiowzz","abcczz"]
 *
 * Explanation:
 *
 * master.guess("aaaaaa") returns -1, because "aaaaaa" is not in wordlist.
 * master.guess("acckzz") returns 6, because "acckzz" is secret and has all 6 matches.
 * master.guess("ccbazz") returns 3, because "ccbazz" has 3 matches.
 * master.guess("eiowzz") returns 2, because "eiowzz" has 2 matches.
 * master.guess("abcczz") returns 4, because "abcczz" has 4 matches.
 * We made 5 calls to master.guess and one of them was the secret, so we pass the test case.
 *
 * Note:  Any solutions that attempt to circumvent the judge will result in disqualification.
 *
 */
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

// This is the Master's API interface.
// You should not implement it, or speculate about its implementation
class Master {
 public:
  int guess(string word);
};

class Solution1 {
 private:
  // 计算两个单词的匹配数
  int getMatch(const string& a, const string& b) {
    int cnt = 0;
    for (int i = 0; i < 6; ++i) {
      if (a[i] == b[i]) cnt++;
    }
    return cnt;
  }

 public:
  void findSecretWord(vector<string>& wordlist, Master& master) {
    int n = wordlist.size();
    vector<bool> candidate(n, true);  // 标记哪些单词仍在候选集中
    srand(time(nullptr));

    for (int guessCount = 0; guessCount < 10; ++guessCount) {
      // 1. 从候选集中随机选一个单词
      int guessIdx = rand() % n;
      while (!candidate[guessIdx]) {
        guessIdx = rand() % n;
      }

      // 2. 进行猜测
      int match = master.guess(wordlist[guessIdx]);
      if (match == 6) return;  // 猜中了

      // 3. 根据反馈筛选候选集
      candidate[guessIdx] = false;  // 当前猜测词本身（如果不是秘密）被淘汰
      for (int i = 0; i < n; ++i) {
        if (candidate[i] && getMatch(wordlist[i], wordlist[guessIdx]) != match) {
          candidate[i] = false;
        }
      }
    }
  }
};

class Solution2 {
private:
    // 预计算所有单词两两之间的匹配数
    vector<vector<int>> precomputeMatches(vector<string>& wordlist) {
        int n = wordlist.size();
        vector<vector<int>> matches(n, vector<int>(n, 0));
        for (int i = 0; i < n; ++i) {
            for (int j = i; j < n; ++j) {
                int cnt = 0;
                for (int k = 0; k < 6; ++k) {
                    if (wordlist[i][k] == wordlist[j][k]) cnt++;
                }
                matches[i][j] = matches[j][i] = cnt;
            }
        }
        return matches;
    }

public:
    void findSecretWord(vector<string>& wordlist, Master& master) {
        int n = wordlist.size();
        auto matches = precomputeMatches(wordlist);
        vector<bool> candidate(n, true);

        for (int guessCount = 0; guessCount < 10; ++guessCount) {
            // 1. 选择最佳猜测词（Minimax 策略）
            int bestGuess = -1;
            int bestScore = n + 1; // 初始化一个较大的数

            for (int i = 0; i < n; ++i) {
                if (!candidate[i]) continue;

                // 统计如果选择 i，每个匹配数对应的候选组大小
                vector<int> groups(7, 0); // 匹配数 0-6
                for (int j = 0; j < n; ++j) {
                    if (candidate[j]) {
                        groups[matches[i][j]]++;
                    }
                }

                // 取该猜测对应的最大组大小（最坏情况）
                int maxGroup = 0;
                for (int k = 0; k <= 6; ++k) {
                    maxGroup = max(maxGroup, groups[k]);
                }

                // 选择能最小化最坏情况的单词
                if (maxGroup < bestScore) {
                    bestScore = maxGroup;
                    bestGuess = i;
                }
            }

            // 2. 进行猜测
            int match = master.guess(wordlist[bestGuess]);
            if (match == 6) return;

            // 3. 根据反馈筛选候选集
            candidate[bestGuess] = false;
            for (int i = 0; i < n; ++i) {
                if (candidate[i] && matches[i][bestGuess] != match) {
                    candidate[i] = false;
                }
            }
        }
    }
};