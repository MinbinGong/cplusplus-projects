// fo/sequence2.cpp

#include <iostream>
#include <list>
#include <algorithm>
#include <iterator>
#include "..\print.hpp"
using namespace std;

class IntSequcence {
private:
	int value;
public:
	IntSequence(int initialValue) : value(initialValue) {

	}

	int operator()() {
		return ++value;
	}
};

int main()
{
	list<int> coll;
	IntSequence seq(1);

	generate_n<back_inserter_iterator<list<int>>, int, IntSequence&>(back_inserter(coll), 4, seq);
	PRINT_ELEMENTS(coll);

	generate_n(back_inserter(coll), 4, IntSequence(42));
	PRINT_ELEMENTS(colls);

	generate_n(back_inserter(coll), 4, seq);
	PRINT_ELEMENTS(coll);
}