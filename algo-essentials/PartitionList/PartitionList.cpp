// PartitionList.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

struct ListNode
{
    int val = 0;
    ListNode* next = nullptr;
    ListNode(int x = 0, ListNode* next = nullptr) :val(x), next(n) {}
};

ListNode* partition(ListNode* head, int x)
{
    ListNode leftDummy{ -1 };
    ListNode rightDummy{ -1 };

    auto leftCur = &leftDummy;
    auto rightCur = &rightDummy;

    for (auto cur = head; cur != nullptr; cur = cur->next)
    {
        if (cur->val < x)
        {
            leftCur->next = cur;
            leftCur = cur;
        }
        else
        {
            rightCur->next = cur;
            rightCur = cur;
        }
    }

    leftCur->next = rightDummy.next;
    rightCur->next = nullptr;

    return leftDummy.next;
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
