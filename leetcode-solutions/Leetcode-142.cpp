/*
 * Linked List Cycle II
 */

ListNode* detectCycle(ListNode* head)
{
	ListNode* fast{ head }, * slow{ head };
	bool hasCycle{ false };

	while (fast && fast->next)
	{
		fast = fast->next->next;
		slow = slow->next;
		if (fast == slow)
		{
			hasCycle = true;
			break;
		}
	}

	if (!hasCycle)
		return nullptr;

	fast = head;
	while (fast != slow)
	{
		fast = fast->next;
		slow = slow->next;
	}
	return fast;
}