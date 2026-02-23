/*
 * Split Linked List in Parts
 *
 * Given a (singly) linked list with head node root, write a function to split the linked list into k consecutive linked
 * list "parts".
 *
 * The length of each part should be as equal as possible: no two parts should have a size differing by more than 1.
 * This may lead to some parts being null.
 *
 * The parts should be in order of occurrence in the input list, and parts occurring earlier should always have a size
 * greater than or equal parts occurring later.
 *
 * Return a List of ListNode's representing the linked list parts that are formed.
 *
 * Examples 1->2->3->4, k = 5 // 5 equal parts [ [1], [2], [3], [4], null ]
 *
 * Note:
 * 1. The length of root will be in the range [0, 1000].
 * 2. Each value of a node in the input will be an integer in the range [0, 999].
 * 3. k will be an integer in the range [1, 50].
 *
 */
#include <vector>
using namespace std;

// Definition for singly-linked list.
struct ListNode {
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
 public:
  vector<ListNode*> splitListToParts(ListNode* head, int k) {
    // Compute length of the list
    int len = 0;
    ListNode* cur = head;
    while (cur) {
      len++;
      cur = cur->next;
    }

    int baseSize = len / k;   // minimum size of each part
    int remainder = len % k;  // number of parts that get an extra node

    vector<ListNode*> result(k, nullptr);
    cur = head;
    ListNode* prev = nullptr;

    for (int i = 0; i < k; ++i) {
      result[i] = cur;  // start of current part

      int partSize = baseSize + (i < remainder ? 1 : 0);
      // Move cur to the first node of the next part
      for (int j = 0; j < partSize; ++j) {
        prev = cur;
        if (cur) cur = cur->next;
      }

      // Cut off the current part from the rest of the list
      if (prev) prev->next = nullptr;
    }

    return result;
  }
};