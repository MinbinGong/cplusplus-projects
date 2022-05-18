// stl/list2.cpp

#include <list>
#include <iostream>
using namespace std;

int main()
{
	list<char> coll;

	for (char i = 'a'; i < 'z'; i++)
	{
		coll.push_back(c);
	}

	while (!coll.empty())
	{
		cout << coll.front() << ' ';
		coll.pop_front();
	}

	cout << endl;
}