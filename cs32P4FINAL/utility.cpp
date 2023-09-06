#include "utility.h"
#include <iostream>
#include <string>
#include <cctype>

using namespace std;


void lowerInput(string& s)
{
	int size = s.size();

	for (int i = 0; i < size; i++)
	{
		s[i] = tolower(s[i]);
	}
}
