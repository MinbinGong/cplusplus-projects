/*
 * leetcode-369: Plus One Linked List
 *
 * Given a non-negative integer represented as a linked list of digits, plus one to the integer.
 *
 * The digits are stored such that the most significant digit is at the head of the list.
 *
 * Example 1:
 * Input: head = [1,2,3]
 * Output: [1,2,4]
 *
 * Example 2:
 * Input: head = [0]
 * Output: [1]
 *
 * Constraints:
 * The number of nodes in the linked list is in the range [1, 100].
 * 0 <= Node.val <= 9
 * The number represented by the linked list does not contain leading zeros except for the zero itself.
 *
 */
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
  ListNode* plusOne(ListNode* head) {
    // Sentinel node to handle carry overflow at the head
    ListNode* dummy = new ListNode(0);
    dummy->next = head;

    // Find the rightmost node that is not 9
    ListNode* notNine = dummy;  // last node that is not 9
    ListNode* curr = head;

    while (curr) {
      if (curr->val != 9) {
        notNine = curr;
      }
      curr = curr->next;
    }

    // Increment the notNine node by 1
    notNine->val++;
    // Set all following nodes to 0
    curr = notNine->next;
    while (curr) {
      curr->val = 0;
      curr = curr->next;
    }

    // If dummy became 1, return dummy; otherwise return dummy->next
    if (dummy->val == 1) {
      return dummy;
    } else {
      ListNode* result = dummy->next;
      delete dummy;
      return result;
    }
  }
};