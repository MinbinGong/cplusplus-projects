/*
  Reverse Linked List

  题目描述
  翻转一个链表

  题解
  链表翻转是非常基础也一定要掌握的技能。我们提供了两种写法——递归和非递归，且我们
  建议你同时掌握这两种写法。
 */
struct ListNode {
  int val = 0;
  ListNode *next = nullptr;
  explicit ListNode(int x, ListNode *n = nullptr) : val(x), next(n) {}
};

ListNode *reverseListRecursive(ListNode *head, ListNode *prev = nullptr) {
  if (head == nullptr) {
    return prev;
  }
  ListNode *next = head->next;
  head->next = prev;
  return reverseListRecursive(next, head);
}

ListNode *reverseListIterative(ListNode *head) {
  ListNode *prev = nullptr, *next;
  while (head) {
    next = head->next;
    head->next = prev;
    prev = head;
    head = next;
  }
  return prev;
}