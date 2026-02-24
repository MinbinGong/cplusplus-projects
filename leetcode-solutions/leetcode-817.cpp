/*
 * 817. Linked List Components
 *
 * We are given head, the head node of a linked list containing unique integer values.
 *
 * We are also given the list G, a subset of the values in the linked list.
 *
 * Return the number of connected components in G, where two values are connected if they appear consecutively in the
 * linked list.
 *
 * Example:
 * Input:
 * head: 0->1->2->3
 * G = [0, 1, 3]
 * Output: 2
 * Explanation:
 * 0 and 1 are connected, so [0, 1] and [3] are the two connected components.
 *
 * Note:
 * If N is the length of the linked list given by head, 1 <= N <= 10000.
 * The value of each node in the linked list will be in the range [0, N - 1].
 * 1 <= G.length <= 10000.
 * G is a subset of all values in the linked list.
 *
 */
#include <vector>
#include <unordered_set>
using namespace std;
/**
 * Definition for singly-linked list.
 */
struct ListNode {
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
 public:
  int numComponents(ListNode* head, vector<int>& G) {
    unordered_set<int> values(G.begin(), G.end());
    int ans = 0;
    bool inComponent = false;
    ListNode* cur = head;
    while (cur) {
      if (values.count(cur->val)) {
        if (!inComponent) {
          ++ans;
          inComponent = true;
        }
      } else {
        inComponent = false;
      }
      cur = cur->next;
    }
    return ans;
  }
};