/**
 * 1836. Remove Duplicates From an Unsorted Linked List
 * https://leetcode.com/problems/remove-duplicates-from-an-unsorted-linked-list/
 * 
 * Given the head of a linked list, find all the values that appear more than once in the list and delete the nodes that have any of those values.
 * 
 * Return the linked list after the deletions.
 * 
 * Example 1:
 * Input: head = [1,2,3,2]
 * Output: [1,3]
 * Explanation: 2 appears twice in the linked list, so all 2's should be deleted. After deleting all 2's, we are left with [1,3].
 * 
 * Example 2:
 * Input: head = [2,1,1,2]
 * Output: []
 * Explanation: 2 and 1 both appear twice. All the elements should be deleted.
 * 
 * Example 3:
 * Input: head = [3,2,2,1,3,2,4]
 * Output: [1,4]
 * Explanation: 3 appears twice in the linked list, so all 3's should be deleted. After deleting all 3's, we are left with [1,4].
 * 
 * Constraints:
 * The number of nodes in the list is in the range [1, 105]
 * 1 <= Node.val <= 105
 * 
 */
#include <unordered_set>

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* removeDuplicates(ListNode* head) {
        if (!head) return nullptr;
        
        std::unordered_set<int> seen;
        ListNode* prev = nullptr;
        ListNode* curr = head;
        
        while (curr) {
            if (seen.find(curr->val) != seen.end()) {
                // Duplicate found – skip this node
                prev->next = curr->next;
                delete curr;          // free memory (optional)
                curr = prev->next;
            } else {
                // New value – keep it
                seen.insert(curr->val);
                prev = curr;
                curr = curr->next;
            }
        }
        return head;
    }
};