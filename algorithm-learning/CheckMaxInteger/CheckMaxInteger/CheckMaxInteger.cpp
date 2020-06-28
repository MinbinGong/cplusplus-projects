// CheckMaxInteger.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <algorithm>

int main()
{
    std::string src{ "               -Hello World!\n" };

    auto itr = std::find_if_not(src.begin(), src.end(), isspace);

    src.erase(src.begin(), itr);

    std::cout << src << std::endl;

    return 0;
}