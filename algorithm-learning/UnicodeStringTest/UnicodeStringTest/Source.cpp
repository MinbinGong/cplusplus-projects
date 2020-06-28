#include <iostream>
#include <string>
using namespace std;

int main()
{
	std::string src1{ "Hello" };
	std::string src2{ "中国人" };

	long ret = 0;
	{
		for (const auto &item : src1)
		{
			ret += static_cast<long>(item);
		}
		cout << ret << endl;
	}

	ret = 0;
	{
		for (const auto &item : src2)
		{
			ret += static_cast<long>(item);
		}
		cout << ret << endl;
	}

	return 0;
}