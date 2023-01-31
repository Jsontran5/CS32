#include "Set.h"
#include <iostream>
#include <cassert>
using namespace std;


void test() {
    Set s;
    Set a;

    assert(s.empty()); // check to see if s set is empty
    assert(a.empty()); // check to see if a set is empty


    s.insert(123456789);
    s.insert(37);
    assert(s.size() == 2);
    s.dump();
}



int main()
{
	test();
	cout << "Passed all tests" << endl;
}