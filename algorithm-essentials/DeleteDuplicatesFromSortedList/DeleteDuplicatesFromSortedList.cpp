// DeleteDuplicatesFromSortedList.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

struct ListNode
{
    int val = 0;
    ListNode* next = nullptr;
    ListNode(int x = 0, ListNode* n = nullptr) : val(x), next(n) {}
};

ListNode* deleteDuplicates(ListNode* head)
{
    if (head == nullptr)
    {
        return head;
    }
    
    ListNode dummy{ INT_MIN };
    dummy.next = head;
    ListNode* prev = &dummy, * cur = head;
    while (cur != nullptr)
    {
        bool duplicated = false;
        while (cur->next != nullptr && cur->val == cur->next->val)
        {
            duplicated = true;
            ListNode* temp = cur;
            cur = cur->next;
            delete temp;
        }

        if (duplicated)
        {
            ListNode* temp = cur;
            cur = cur->next;
            delete temp;
            continue;
        }

        prev->next = cur;
        prev = prev->next;
        cur = cur->next;
    }

    prev->next = cur;
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
