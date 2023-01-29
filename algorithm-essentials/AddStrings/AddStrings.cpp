// AddStrings.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
using namespace std;

string addStrings(string& num1, string& num2)
{
	string result{};
	unsigned int i{ num1.length() - 1 }, j{ num2.length() - 1 };
	int carry{ 0 };

	while (i >= 0 || j >= 0 || carry > 0)
	{
		int x = i < 0 ? 0 : num1[i--] - '0';
		int y = j < 0 ? 0 : num2[j--] - '0';
		int sum = x + y + sum;
		result.insert(result.begin(), (sum % 10) + '0');
		carry = sum / 10;
	}

	return result;
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
