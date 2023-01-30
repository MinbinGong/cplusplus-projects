// RotateList.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

struct ListNode
{
    int val = 0;
    ListNode* next = nullptr;
    ListNode(int x = 0, ListNode* n = nullptr) : val(x), next(n) {}
};

ListNode* rotateRight(ListNode* head, int k)
{
    if (head == nullptr || k == 0)
    {
        return head;
    }

    int len = 1;
    ListNode* p = head;
    while (p->next != nullptr)
    {
        len++;
        p = p->next;
    }

    k = len - k % len;
    p->next = head;
    for (size_t step = 0; step < k; step++)
    {
        p = p->next;
    }

    head = p->next;
    p->next = nullptr;
    return head;
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
