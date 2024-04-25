/*
 * Insertion Sort List
 *
 * Given the head of a singly linked list, sort the list using insertion sort,
 * and return the sorted list's head.
 *
 * The steps of the insertion sort algorithm:
 *
 * Insertion sort iterates, consuming one input element each repetition and
 * growing a sorted output list.
 * At each iteration, insertion sort removes one element from the input data,
 * finds the location it belongs within the sorted list and inserts it there.
 * It repeats until no input elements remain.
 */
struct ListNode {
  int val = 0;
  ListNode *next = nullptr;
  explicit ListNode(int x = 0, ListNode *n = nullptr) : val(x), next(n) {}
};

ListNode *insertionSortList(ListNode *head) {
  ListNode *start = new ListNode(-1);
  start->next = head;
  ListNode *cur = head;
  ListNode *prev = start;

  while (cur) {
    if (cur->next && cur->next->val < cur->val) {
      while (prev->next && prev->next->val < cur->next->val) {
        prev = prev->next;
      }

      ListNode *temp = prev->next;
      prev->next = cur->next;
      cur->next = cur->next->next;
      prev->next->next = temp;

      prev = start;
    } else {
      cur = cur->next;
    }
  }
  return start->next;
}
