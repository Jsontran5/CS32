#include "Set.h"
#include <iostream>
#include <cassert>
using namespace std;


void test() {
  

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
    
	s.dump();

	
	
}



int main()
{
	test();
	cout << "Passed all tests" << endl;
}