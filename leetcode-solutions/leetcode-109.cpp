/*
 * Convert Sorted List to Binary Search Tree
 * Given the head of a singly linked list where elements are sorted in ascending order,
 * convert it to a height-balanced binary search tree.
 *
 * Constraints:
 * 1. The number of nodes in head is in the range [0, 2 * 104].
 * 2. -105 <= Node.val <= 105
 */
struct ListNode {
  int val = 0;
  ListNode *next = nullptr;
  explicit ListNode(int x = 0, ListNode *n = nullptr) : val(x), next(n) {}
};

struct TreeNode {
  int val = 0;
  TreeNode *left = nullptr;
  TreeNode *right = nullptr;
  TreeNode(int x = 0, TreeNode *l = nullptr, TreeNode *r = nullptr) : val(x), left(l), right(r) {}
};

TreeNode* sortedListToBST(ListNode* head) {
  if (head == nullptr) return nullptr;

  ListNode *slow = head;
  ListNode *fast = head;
  ListNode *prev = nullptr;

  while (fast != nullptr && fast->next != nullptr) {
    prev = slow;
    slow = slow->next;
    fast = fast->next->next;
  }

  TreeNode *root = new TreeNode(slow->val);
  if (slow == head) {
    return root;
  }

  prev->next = nullptr;
  root->left = sortedListToBST(head);
  root->right = sortedListToBST(slow->next);

  return root;
}

