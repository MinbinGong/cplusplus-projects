#include <iostream>
using namespace std;

class A
{
public:
	int mData;
};

class B : public A
{
	void increaseData()
	{
		++mData;
	}
};

class C : public A
{
	int getData()
	{
		return mData;
	}
};

int main()
{
	B b;
	C c;
	
	b.mData = 1;
	cout << c.getData() << endl;

	return 0;
}