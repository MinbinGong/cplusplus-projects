// InitializerTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <vector>

typedef struct {
    std::string type;
    std::string value;
}Phone;

int main()
{
    std::vector<Phone> src;

    src.emplace_back({ "asd", "1234" });
    src.emplace_back({ "asdf", "3234" });

    for (auto const &item : src)
    {
        std::cout << item.type << " : " << item.value << "\n";
    }

    return 0;
}