// CopyRandomList.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

struct RandomList
{
    int val = 0;
    RandomList* next = nullptr;
    RandomList* random = nullptr;
    RandomList(int x = 0, RandomList* n = nullptr, RandomList* r = nullptr) : val(x), next(n), random(r) {}
};

RandomList* copyRandomList(RandomList* head)
{
    for (RandomList* cur = head; cur != nullptr; )
    {
        RandomList* node = new RandomList(cur->val);
        node->next = cur->next;
        cur->next = node;
        cur = node->next;
    }

    for (RandomList* cur = head; cur != nullptr; )
    {
        if (cur->random != nullptr)
        {
            cur->next->random = cur->random->next;
        }

        cur = cur->next->next;
    }

    RandomList dummy{ -1 };
    for (RandomList* cur = head, *newCur = &dummy; cur != nullptr; )
    {
        newCur->next = cur->next;
        newCur = newCur->next;
        cur->next = cur->next->next;
        cur = cur->next;
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
