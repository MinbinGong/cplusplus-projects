// FindMissingNumber.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <vector>
using namespace std;

int getMissingNumber(vector<int>& src);

int main()
{
    vector<int> arr{ 1,2,4,5,6 };
    int miss = getMissingNumber(arr);
    cout << miss << endl;
}

int getMissingNumber(vector<int>& src)
{
    int x1 = src.at(0);
    int x2 = 1;

    for (auto itr = src.cbegin() + 1; itr != src.cend() + 1; ++itr)
    {
        x1 = x1 ^ (*itr);
    }

    for (unsigned int i = 2; i < )
    {
    }
}