/*
 * Flatten a Multilevel Doubly Linked List
 * 
 * You are given a doubly linked list, which contains nodes that have a next pointer, a previous pointer, and an additional child pointer. This child pointer may or may not point to a separate doubly linked list, also containing these special nodes. These child lists may have one or more children of their own, and so on, to produce a multilevel data structure as shown in the example below.
 * Given the head of the first level of the list, flatten the list so that all the nodes appear in a single-level, doubly linked list. Let curr be a node with a child list. The nodes in the child list should appear after curr and before curr.next in the flattened list.
 * Return the head of the flattened list. The nodes in the list must have all of their child pointers set to null.
 * 
 * Example 1:
 * Input: head = [1,2,3,4,5,6,null,null,null,7,8,9,10,null,null,11,12]
 * Output: [1,2,3,7,8,11,12,9,10,4,5,6]
 * 
 * Example 2:
 * Input: head = [1,2,null,3]
 * Output: [1,3,2]
 * Explanation: The input multilevel linked list is as follows:
 * 
 * Example 3:
 * Input: head = []
 * Output: []
 * 
 * Constraints:
 * The number of Nodes will not exceed 1000.
 * 1 <= Node.val <= 10^5
 * 
 */

class Node {
 public:
  int val;
  Node *prev;
  Node *next;
  Node *child;
};

Node *dfs(Node *node) {
  if (node->child == nullptr && node->next == nullptr) {
    return node;
  }

  Node *child = node->child;
  Node *next = node->next;

  if (child) {
    Node *tail = dfs(child);
    if (next) {
      tail->next = next;
      next->prev = tail;
    }

    node->child = nullptr;
    node->next = child;
    child->prev = node;

    if (tail->next) {
      return dfs(tail->next);
    }

    return tail;
  }

  return dfs(node->next);
}

Node *flatten(Node *head) {
  if (head == nullptr) return head;

  dfs(head);
  return head;
}