// AddTwoNums.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

struct ListNode
{
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* n) : val(x), next(n) {}
};

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
{
	ListNode dummy(-1);
	int carry = 0;
	ListNode* prev = &dummy;
	for (ListNode* pa = l1, *pb = l2;
		 pa != nullptr || pb != nullptr;
		 pa = pa == nullptr ? nullptr : pa->next, pb = pb == nullptr ? nullptr : pb->next, prev = prev->next) {
		const int ai = pa == nullptr ? 0 : pa->val;
		const int bi = pb == nullptr ? 0 : pb->val;
		const int value = (ai + bi + carry) % 10;
		carry = (ai + bi + carry) / 10;
		prev->next = new ListNode(value);
	}

	if (carry > 0)
	{
		prev->next = new ListNode(carry);
	}

	return dummy.next;
}

int main()
{
	std::cout << "Hello World!\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
