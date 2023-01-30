// ReorderList.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

struct ListNode
{
    int val = 0;
    ListNode* next = nullptr;
    ListNode(int x = 0, ListNode* n = nullptr) : val(x), next(n) {}
};

ListNode* reverse(ListNode* head)
{
    if (head == nullptr || head->next == nullptr)
    {
        return head;
    }

    ListNode* prev = head;
    for (ListNode* curr = head->next, *next = curr->next; curr != nullptr; prev = curr, curr = next, next = next != nullptr ? next->next : nullptr)
    {
        curr->next = prev;
    }

    head->next = nullptr;
    return prev;
}

void reorderList(ListNode* head)
{
    if (head == nullptr|| head->next == nullptr)
    {
        return;
    }

    ListNode* slow = head, * fast = head, * prev = nullptr;
    while (fast != nullptr && fast->next != nullptr)
    {
        prev = slow;
        slow = slow->next;
        fast = fast->next->next;
    }

    prev->next = nullptr;
    slow = reverse(slow);

    ListNode* curr = head;
    while (curr->next != nullptr)
    {
        ListNode* tmp = curr->next;
        curr->next = slow;
        slow = slow->next;
        curr->next->next = tmp;
        curr = tmp;
    }

    curr->next = slow;
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
