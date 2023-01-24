#include "Set.h"
#include <iostream>
#include <cassert>
using namespace std;

int main() {
	Set s;
	assert(s.empty());
	s.insert(10000);
	s.insert(20000);
	assert(!s.insert(10000));
	assert(!s.erase(450000));
	cout << "All Tests Passed" << endl;
}