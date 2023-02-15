#include <iostream>
#include <cassert>
using namespace std; //DELETE HERE




// Return the number of ways that all n1 elements of a1 appear in
	  // the n2 element array a2 in the same order (though not necessarily
	  // consecutively).  We decree that the empty sequence (i.e. one where
	  // n1 is 0) appears in a sequence of length n2 in 1 way, even if n2
	  // is 0.  For example, if a2 is the 7 element array
	  //	10 50 40 20 50 40 30
	  // then for this value of a1     the function must return
	  //	10 20 40                        1
	  //	10 40 30                        2
	  //	20 10 40                        0
	  //	50 40 30                        3
int countIsIn(const double a1[], int n1, const double a2[], int n2)
{
	if (n1 == 0 && n2 == 0)
	{
		return 1;
	}

	if (n2 < n1 && n2 <= 0)
	{
		return 0;
	}

	if ((n1 == 1 && n2 == 1) && (a1[0] == a2[0]))
	{
		return 1;
	}
		
	if (n1 <= 0)
	{
		return 1;
	}


	if (a1[0] == a2[0])
		return countIsIn(a1 , n1 , a2 +1, n2-1 ) + countIsIn(a1 + 1, n1 - 1, a2+1, n2-1);
	else
	{
		return countIsIn(a1 , n1 , a2+1, n2-1);
	}
	
}


int main()
{
	double d[] = { -1, 2, -3, -3, -1, 4, -5 };
	int arrLen = 7;
	cout << "before order" << endl;
	for (int i = 0; i < arrLen; i++) {
		cout << d[i] << endl;
	}
	//order(d, arrLen);
	cout << "after order" << endl;
	for (int i = 0; i < arrLen; i++) {
		cout << d[i] << endl;
	}
	double a2[] = { 10, 50, 40, 20, 50, 40, 30 };
	double a11[] = { 10, 20, 40 };
	double a12[] = { 10, 40, 30 };
	double a13[] = { 20, 10, 40 };
	double a14[] = { 50, 40, 30 };
	assert(countIsIn(a11, 3, a2, 7) == 1);
	
	assert(countIsIn(a12, 3, a2, 7) == 2);
	assert(countIsIn(a13, 3, a2, 7) == 0);
	assert(countIsIn(a14, 3, a2, 7) == 3);
	
	assert(countIsIn(a14, 0, a2, 0) == 1);
	cout << "TEST " << countIsIn(a14, -1, a2, 0) << endl;
	assert(countIsIn(a14, -1, a2, 0) == 1);
	assert(countIsIn(a14, -1, a2, -1) == 1);
	assert(countIsIn(a14, 1, a2, 0) == 0);
	assert(countIsIn(a14, 1, a2, -1) == 0);
	cout << "FINISHED" << endl;
}