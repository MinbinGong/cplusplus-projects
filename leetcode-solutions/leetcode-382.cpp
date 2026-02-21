/*
 * Linked List Random Node
 *
 * Given a singly linked list, return a random node's value from the linked list. Each node must have the same probability of being chosen.
 * 
 * Implement the Solution class:
 * 
 * Solution(ListNode head) Initializes the object with the head of the singly-linked list head.
 * int getRandom() Chooses a node randomly from the list and returns its value. All the nodes of the list should be equally likely to be chosen.
 * 
 */
#include <random>
using namespace std;

struct ListNode {
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* n) : val(x), next(n) {}
};

int getRandom(ListNode* head) {
  int ans = head->val;
  ListNode* node = head->next;
  int i = 2;
  while (node) {
    if ((rand() % i) == 0) {
      ans = node->val;
    }
    ++i;
    node = node->next;
  }
  return ans;
}