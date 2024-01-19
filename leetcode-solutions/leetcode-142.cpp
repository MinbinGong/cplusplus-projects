/*
 * Linked List Cycle II
 *
 * 题目描述
 * 给定一个链表，如果有环路，找出环路的开始点。
 *
 * 题解
 * 对于链表找环路的问题，有一个通用的解法——快慢指针（Floyd 判圈法）。给定两个指针，
 * 分别命名为 slow 和 fast，起始位置在链表的开头。每次 fast 前进两步，slow 前进一步。如果 fast
 * 可以走到尽头，那么说明没有环路；如果 fast 可以无限走下去，那么说明一定有环路，且一定存
 * 在一个时刻 slow 和 fast 相遇。当 slow 和 fast 第一次相遇时，我们将 fast 重新移动到链表开头，并
 * 让 slow 和 fast 每次都前进一步。当 slow 和 fast 第二次相遇时，相遇的节点即为环路的开始点。
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

ListNode* detectCycle(ListNode* head) {
    ListNode *slow = head, *fast = head;

    do {
        if (!fast || !fast->next)
            return nullptr;
        fast = fast->next->next;
        slow = slow->next;
    } while (fast != slow);

    fast = head;
    while (fast != slow) {
        slow = slow->next;
        fast = fast->next;
    }

    return fast;
}
