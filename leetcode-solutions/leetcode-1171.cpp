/*
 * 1171. Remove Zero Sum Consecutive Nodes from Linked List
 * 
 * Given the head of a linked list, we repeatedly delete consecutive sequences of nodes that sum to 0 until there are no such sequences.
 * 
 * After doing so, return the head of the final linked list.  You may return any such answer.
 * 
 * Example 1:
 * Input: head = [1,2,-3,3,1]
 * Output: [3,1]
 * Note: The answer [1,2,1] would also be accepted.
 * 
 * Example 2:
 * Input: head = [1,2,3,-3,4]
 * Output: [1,2,4]
 * 
 * Example 3:
 * Input: head = [1,2,3,-3,-2]
 * Output: [1]
 * 
 * Note:
 * The given linked list will contain between 1 and 1000 nodes.
 * Each node in the linked list has -1000 <= node.val <= 1000.
 */
#include <unordered_map>
using namespace std;

/**
 * Definition for singly-linked list.
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
    ListNode* removeZeroSumSublists(ListNode* head) {
        // Dummy node to handle cases where head itself is removed
        ListNode dummy(0);
        dummy.next = head;
        
        // Map from prefix sum to the node where that sum first occurs
        unordered_map<int, ListNode*> seen;
        seen[0] = &dummy;   // prefix sum 0 before the first node
        
        int sum = 0;
        ListNode* cur = head;
        
        while (cur) {
            sum += cur->val;          // running prefix sum
            
            if (seen.count(sum)) {    // zero‑sum sublist found
                ListNode* prev = seen[sum];          // node before the sublist
                ListNode* toRemove = prev->next;     // first node of sublist
                int tempSum = sum;
                
                // Erase all prefix sums corresponding to nodes inside the sublist
                // (except the node 'prev' itself)
                while (toRemove != cur) {
                    tempSum += toRemove->val;        // reconstruct prefix sum at toRemove
                    seen.erase(tempSum);
                    toRemove = toRemove->next;
                }
                
                // Remove the whole sublist by linking prev directly to cur->next
                prev->next = cur->next;
                
                // Reset cur to prev (so that after the loop increment we continue
                // with the node right after the removed segment)
                cur = prev;
            } else {
                // First time seeing this prefix sum – store it
                seen[sum] = cur;
            }
            
            cur = cur->next;
        }
        
        return dummy.next;
    }
};