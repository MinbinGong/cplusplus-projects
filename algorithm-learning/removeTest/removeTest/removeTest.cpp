// removeTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

int main()
{
    std::vector<std::string> stringVec{ "Hell", "Woo", "Hello", "World", "Hell" };
    std::string testString{ "Hell" };

    //auto removeElem = [&](std::string src) -> bool
    //{
    //    return src == testString;
    //};
    //auto itr = std::remove_if(stringVec.begin(), stringVec.end(), removeElem);

    auto itr = std::remove_if(stringVec.begin(), stringVec.end(), [&testString](auto item) {
        return testString.compare(item) == 0;
    });
    stringVec.erase(itr, stringVec.end());

    for (auto const &item : stringVec)
    {
        std::cout << item << " ";
    }
    std::cout << std::endl;

    return 0;
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
