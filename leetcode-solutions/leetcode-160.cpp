/*
Intersection of two linked list

题目描述
给定两个链表，判断它们是否相交于一点，并求这个相交节点

题解
假设链表 A 的头节点到相交点的距离是 a，链表 B 的头节点到相交点的距离是 b，相交点
到链表终点的距离为 c。我们使用两个指针，分别指向两个链表的头节点，并以相同的速度前进，
若到达链表结尾，则移动到另一条链表的头节点继续前进。按照这种前进方法，两个指针会在
a + b + c 次前进后同时到达相交节点
*/

struct ListNode {
    int val = 0;
    ListNode* next = nullptr;
    explicit ListNode(int x = 0, ListNode* n = nullptr) : val(x), next(n) {}
};

ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
    ListNode *l1 = headA, *l2 = headB;
    while (l1 != l2) {
        l1 = l1 ? l1->next : headB;
        l2 = l2 ? l2->next : headA;
    }
    return l1;
}