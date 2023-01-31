#include "Set.h"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
    Set a;
    Set b;				// Check copy constructor
    Set c;
    				// Check assignment operator

    a.insert("first");
    a.insert("second");
    a.insert("third");

    b.insert("first");
    b.insert("second");
    b.insert("third");
    b.insert("fourth");
    
    unite(a, b, c);
    assert(c.contains("first") && c.contains("second") && c.contains("fourth") && c.contains("third"));
}

int main()
{
    test();
    cout << "Passed all tests" << endl;
}