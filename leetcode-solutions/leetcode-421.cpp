#include <vector>
using namespace std;

struct TrieNode {
  vector<TrieNode *> child;
  bool last;
  TrieNode() : child(2, NULL), last(false){};
};

void insert(TrieNode *root, int val) {
  TrieNode *cur = root;
  for (int i = 31; i >= 0; i--) {
    int v = (val >> i) & 1;
    if (!cur->child[v]) cur->child[v] = new TrieNode();
    cur = cur->child[v];
  }
  cur->last = true;
}

int search(TrieNode *root, int val) {
  TrieNode *cur = root;
  int res = 0;
  for (int i = 31; i >= 0; i--) {
    int v = (val >> i) & 1;
    if (cur->child[1 - v]) {
      res |= ((1 - v) << i);
      cur = cur->child[1 - v];
    } else {
      res |= (v << i);
      cur = cur->child[v];
    }
  }
  return res;
}

int findMaximumXOR(vector<int> &nums) {
  TrieNode *root = new TrieNode();
  int mx = 0;
  for (auto num : nums) insert(root, num);

  for (auto num : nums) {
    mx = max(num ^ search(root, num), mx);
  }
  return mx;
}