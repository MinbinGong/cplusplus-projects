#include <iostream>
#include <stdlib.h>

int reverse(int x);

int main()
{
	int a{ 0 };
	std::cout << "Enter the value: " << std::endl;
	std::cin >> a;

	std::cout << "Original: " << a << std::endl;
	//std::cout << "Abs: " << (~a) << std::endl;
	std::cout << "Reversed: " << reverse(a) << std::endl;

	return 0;
}

int reverse(int x)
{
	bool negative = x < 0 ? true : false;

	//if (negative)
	//{
	//	x = abs(x);
	//}

	int ret{ 0 };
	while (x)
	{
		ret = ret * 10 + x % 10;
		x = x / 10;
	}

	return ret;
}