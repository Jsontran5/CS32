#include <iostream>
#include <cassert>

#include "CardSet.h"

using namespace std;

int main() {

	CardSet test;
	test.add(1);
	test.add(12);
	assert(test.add(12) == false);
	test.add(123);
	test.add(1234);
	test.add(123);
	test.add(12);
	test.add(1);
	assert(test.size() == 4);

	cout << "assertions successful" << endl;
	test.print();
}