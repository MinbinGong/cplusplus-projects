/*
 * Given a linked list, swap every two adjacent nodes and return its head.
 * You must solve the problem without modifying the values in the list's nodes
 * (i.e., only nodes themselves may be changed.)
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *n) : val(x), next(n) {}
};

ListNode *swapPairs(ListNode *head) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }

    ListNode *node = new ListNode(-1);
    ListNode *curr = head, *pre = node;
    while (curr != nullptr && curr->next != nullptr) {
        pre->next = curr->next;
        curr->next = curr->next->next;
        pre->next->next = curr;
        curr = curr->next;
        pre = pre->next->next;
    }

    return node->next;
}
