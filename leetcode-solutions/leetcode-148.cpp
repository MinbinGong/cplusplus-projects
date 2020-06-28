ListNode* sortedMerge(ListNode* l, ListNode* r) {
	if (!l || !r)
		return !l ? r : l;

	ListNode* m;

	if (l->val < r->val) {
		m = l;
		m->next = sortedMerge(l->next, r);
	}
	else {
		m = r;
		m->next = sortedMerge(l, r->next);
	}

	return m;
}

ListNode* frontBackSplit(ListNode* head) {
	ListNode* slow = head, * fast = head->next->next;

	while (fast && fast->next) {
		slow = slow->next;
		fast = fast->next->next;
	}

	return slow;
}

ListNode* sortList(ListNode* head) {
	if (!head || !head->next)
		return head;

	ListNode* m = frontBackSplit(head);
	ListNode* r = sortList(m->next);
	m->next = nullptr;
	ListNode* l = sortList(head);

	return sortedMerge(l, r);
}
