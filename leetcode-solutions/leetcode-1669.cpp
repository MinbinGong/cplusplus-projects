/*
 * 1669. Merge In Between Linked Lists
 * 
 * You are given two linked lists: list1 and list2 of sizes n and m respectively.
 * 
 * Remove list1's nodes from the ath node to the bth node, and put list2 in their place.
 * 
 * The blue edges and nodes in the following figure indicate the result:
 * 
 * Build the result list and return its head.
 * 
 * Example 1:
 * Input: list1 = [10,1,13,6,9,5], a = 3, b = 4, list2 = [1000000,1000001,1000002]
 * Output: [10,1,13,1000000,1000001,1000002,5]
 * Explanation: We remove the nodes 3 and 4 and put the entire list2 in their place. The blue edges and nodes in the above figure indicate the result.
 * 
 * Example 2:
 * Input: list1 = [0,1,2,3,4,5,6], a = 2, b = 5, list2 = [1000000,1000001,1000002,1000003,1000004]
 * Output: [0,1,1000000,1000001,1000002,1000003,1000004,6]
 * Explanation: The blue edges and nodes in the above figure indicate the result.
 * 
 * Constraints:
 * 3 <= list1.length <= 104
 * 1 <= a <= b < list1.length - 1
 * 1 <= list2.length <= 104
 * 
 */
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* mergeInBetween(ListNode* list1, int a, int b, ListNode* list2) {
        // 创建一个哑结点，简化头结点的处理
        ListNode dummy(0);
        dummy.next = list1;
        
        // 找到第 a-1 个结点（prev）
        ListNode* prev = &dummy;
        for (int i = 0; i < a; ++i) {
            prev = prev->next;
        }
        
        // 找到第 b 个结点（nodeB）以及它后面的结点（after）
        ListNode* nodeB = prev->next;          // 第 a 个结点
        for (int i = a; i < b; ++i) {
            nodeB = nodeB->next;
        }
        ListNode* after = nodeB->next;          // 第 b+1 个结点（可能为 nullptr）
        
        // 将 prev->next 指向 list2 的头
        prev->next = list2;
        
        // 找到 list2 的尾结点
        ListNode* tail = list2;
        while (tail->next) {
            tail = tail->next;
        }
        
        // 将 list2 的尾结点连接到 after
        tail->next = after;
        
        // 返回新的头结点
        return dummy.next;
    }
};