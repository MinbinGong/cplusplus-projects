// ListSplice.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <list>

int main()
{
    std::list<int> l1, l2;

    for (auto i = 1; i <= 4; ++i)
    {
        l1.push_back(i);
    }

    for (auto i = 1; i <= 3; ++i)
    {
        l2.push_back(i * 10);
    }

    auto it = l1.begin();
    ++it;

    l1.splice(it, l2);
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
