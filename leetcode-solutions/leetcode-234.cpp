/*
Palindrome linked list

题目描述
以 O„1” 的空间复杂度，判断链表是否回文。

题解
先使用快慢指针找到链表中点，再把链表切成两半；然后把后半段翻转；最后比较两半是否
相等
 */
struct ListNode {
    int val = 0;
    ListNode* next = nullptr;
    explicit ListNode(int x = 0, ListNode* n = nullptr) : val(x), next(n) {}
};

ListNode* reverseList(ListNode* head) {
    ListNode *prev = nullptr, *next;
    while (head) {
        next = head->next;
        head->next = prev;
        prev = head;
        head = next;
    }
    return prev;
}

bool isPalindrome(ListNode* head) {
    if (head == nullptr || head->next == nullptr) {
        return true;
    }
    ListNode *slow = head, *fast = head;
    while (fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    slow->next = reverseList(slow->next);
    slow = slow->next;
    fast = head;
    while (slow) {
        if (fast->val != slow->val) {
            return false;
        }
        fast = fast->next;
        slow = slow->next;
    }
    return true;
}