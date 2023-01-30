// SharedPtrTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <memory>

struct A : public std::enable_shared_from_this<A> {
	std::shared_ptr<A> GetSelf() {
		return shared_from_this();
	}

	~A() {
		std::cout << "A is deleted" << std::endl;
	}
};

int main()
{
	std::cout << "Hello World!\n";
	std::shared_ptr<A> spy(new A);
	std::shared_ptr<A> p = spy->GetSelf();

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
