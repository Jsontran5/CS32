#include "Set.h"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
	Set s;
	Set a;

	assert(s.empty()); // check to see if s set is empty
	assert(a.empty()); // check to see if a set is empty

	unsigned long x = 9876543;
	assert(!s.get(42, x) && x == 9876543); // x unchanged by get failure
	s.insert(123456789);
	assert(s.size() == 1);
	assert(s.get(0, x));
	assert(x == 123456789);
	s.erase(123456789); // erase 123456789
	assert(!s.contains(123456789)); // check if it doesn't contain 123456789
	assert(s.empty()); // check to see if the set is empty
	s.insert(123);
	assert(s.size() == 1); // check size = 1
	s.insert(321);
	assert(s.size() == 2); // check size = 2
	s.insert(222);
	assert(s.size() == 3); // check size = 3
	assert(s.contains(123) && s.contains(222) && s.contains(321));
	// check to see if all numbers are in the set

	a.insert(987); // add 987
	a.insert(789); // add 789

	//check swap function
	s.swap(a);

	unsigned long temp = 0;
	a.get(0, temp);
	assert(temp == 123); //check to see if temp was correctly changed

	assert(!a.get(50, temp)); // get failure

	assert(a.contains(123) && a.contains(222) && a.contains(321));
	//check for correct swap

	assert(s.contains(789) && s.contains(987));//check for correct swap

	a.erase(321);
	assert(a.contains(123)); // check to see if the set still contains 123
	assert(!a.contains(321)); // check to see if the set doesn't contain 321
	assert(a.contains(222)); // check to see if the set still contains 222
	assert(a.size() == 2); // check the size = 2

	//copy constructor
	Set b(a);
	assert(a.contains(123)); // check to see if the set contains 123
	assert(!a.contains(321)); // check to see if the set doesn't contain 321
	assert(a.contains(222)); // check to see if the set contains 222
	assert(a.size() == 2); // check the size = 2

	//test equal operator
	b = s;
	assert(s.contains(789) && s.contains(987));//check for correct operator

	//test out unite function
	unite(s, a, b);
	assert(s.contains(789) && s.contains(987));//check for correct unite
	assert(a.contains(123)); // check to see if the set contains 123
	assert(!a.contains(321)); // check to see if the set doesn't contain 321
	assert(a.contains(222)); // check to see if the set contains 222

	Set c, d, e;
	//add 1,2,3,4
	c.insert(1);
	c.insert(2);
	c.insert(3);
	c.insert(4);

	//add 3,4,5,6
	d.insert(3);
	d.insert(4);
	d.insert(5);
	d.insert(6);

	//subtract the two and make sure 3,4 are gone
	butNot(c, d, e);
	assert(e.contains(1) && e.contains(2));

	//unite c and d and make sure it's only 1,2,5,6
	unite(c, d, e);
	assert(e.contains(1) && e.contains(2) && e.contains(5) && e.contains(6));

	//test out aliasing and make sure it's the same
	unite(e, d, e);
	assert(e.contains(1) && e.contains(2) && e.contains(5) && e.contains(6));
	butNot(e, e, e);
	assert(e.empty());
}

int main()
{
    test();
    cout << "Passed all tests" << endl;
}