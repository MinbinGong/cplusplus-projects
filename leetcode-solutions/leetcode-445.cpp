/*
 * Add Two Numbers II
 *
 * You are given two non-empty linked lists representing two non-negative integers. The most significant digit comes
 * first and each of their nodes contains a single digit. Add the two numbers and return the sum as a linked list.
 *
 * You may assume the two numbers do not contain any leading zero, except the number 0 itself.
 *
 * Constraints:
 * The number of nodes in each linked list is in the range [1, 100].
 * 0 <= Node.val <= 9
 * It is guaranteed that the list represents a number that does not have leading zeros.
 *
 */
#include <stack>
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
  ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    // Use stacks to reverse the order of digits
    stack<int> s1, s2;
    while (l1) {
      s1.push(l1->val);
      l1 = l1->next;
    }
    while (l2) {
      s2.push(l2->val);
      l2 = l2->next;
    }

    int carry = 0;
    ListNode* head = nullptr;

    // Build the result from the least significant digit (top of stacks)
    while (!s1.empty() || !s2.empty() || carry) {
      int sum = carry;
      if (!s1.empty()) {
        sum += s1.top();
        s1.pop();
      }
      if (!s2.empty()) {
        sum += s2.top();
        s2.pop();
      }
      carry = sum / 10;
      // Insert new digit at the front to maintain correct order
      ListNode* newNode = new ListNode(sum % 10);
      newNode->next = head;
      head = newNode;
    }
    return head;
  }
};