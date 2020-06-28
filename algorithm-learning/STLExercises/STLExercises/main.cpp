#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <functional>

#include "fopow.h"

using namespace std;
using namespace std::placeholders;

int main()
{
	vector<int> coll{ 1,2,3,4,5,6,7,8,9 };

	//transform(coll.begin(), coll.end(), 
	//	ostream_iterator<float>(cout, " "), 
	//	bind(fopow<float, int>(), 3, _1));
	//cout << endl;
	//
	//transform(coll.begin(), coll.end(),
	//	ostream_iterator<float>(cout, " "),
	//	bind(fopow<float, int>(), _1, 3));
	//cout << endl;
	//
	//auto plus10 = [](int i) { return i + 10; };
	//cout << "+10 : " << plus10(7) << endl;
	//
	//auto plus10times2 = [](int i) { return (i + 10) * 2; };
	//cout << "+10 * 2: " << plus10times2(7) << endl;
	//
	//auto pow3 = [](int i) { return i*i*i; };
	//cout << "x*x*x: " << pow3(7) << endl;
	//
	//auto inversDivide = [](double d1, double d2) { return d2 / d1; };
	//cout << "invdiv:" << inversDivide(49, 7) << endl;

	long sum = 0;
	for_each(coll.begin(),coll.end(),
		[&sum](int elem) {
		sum += elem;
	});
	double mv = static_cast<double>(sum) / static_cast<double>(coll.size());
	cout << "mean value: " << mv << endl;

	return 0;
}