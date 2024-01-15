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