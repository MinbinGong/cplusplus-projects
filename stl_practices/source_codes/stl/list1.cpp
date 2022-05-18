// stl/list1.cpp

#include <list>
#include <iostream>
using namespace std;

int main()
{
	list<char> coll;

	// append elements from 'a' to 'z'
	for (char i = 'a'; i < 'z'; i++)
	{
		coll.push_back(c);
	}

	// print all elements
	for (auto elem : coll) {
		cout << elem << ' ';
	}
	cout << endl;
}