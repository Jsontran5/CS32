//MAKE SURE TO DELETE EVERYTHING BUT FUNCTIONS
#include<iostream>
#include <string>
#include <cassert>
using namespace std;

bool somePredicate(double x) //DELETE
{
	return x < 0;
}

// Return true if the somePredicate function returns true for at
	  // least one of the array elements; return false otherwise.
bool anyTrue(const double a[], int n)
{

	if (n <= 0)
	{
		return false;
	}

	if (somePredicate(a[0]))
	{
		return true;
	}

	return anyTrue(a + 1, n - 1);


}



// Return the number of elements in the array for which the
// somePredicate function returns true.
int countTrue(const double a[], int n)
{
	
	
	if (n <= 0)
	{
		return 0;
	}
	
	

	if (somePredicate(a[0]))
	{
		
		return 1 + countTrue(a + 1, n - 1);
	}
	

	
	return countTrue(a + 1, n - 1);
}


// Return the subscript of the first element in the array for which
	  // the somePredicate function returns true.  If there is no such
	  // element, return -1.
int firstTrue(const double a[], int n)
{
	if (n <= 0)
	{
		return -1;
	}



	if (somePredicate(a[0]))
	{
		return 0;

	}
	
	int pos = firstTrue(a + 1, n - 1);
	if (pos == -1)
		return -1;

	return pos+1;

}



// Return the subscript of the smallest element in the array (i.e.,
// return the smallest subscript m such that a[m] <= a[k] for all
// k from 0 to n-1).  If the function is told that no doubles are to
// be considered in the array, return -1.
int indexOfMinimum(const double a[], int n)
{
	if (n <= 0)
	{
		return -1;
	}
	if (n == 1)
	{
		return 0;
	}

	int rest = indexOfMinimum(a, n - 1);

	if (a[rest] <= a[n - 1])
	{
		return rest;
	}
	else
		return (n - 1);
}

// If all n1 elements of a1 appear in the n2 element array a2, in
	 // the same order (though not necessarily consecutively), then
	 // return true; otherwise (i.e., if the array a1 is not a
	 // not-necessarily-contiguous subsequence of a2), return false.
	 // (Of course, if a1 is empty (i.e., n1 is 0), return true.)
	 // For example, if a2 is the 7 element array
	 //    10 50 40 20 50 40 30
	 // then the function should return true if a1 is
	 //    50 20 30
	 // or
	 //    50 40 40
	 // and it should return false if a1 is
	 //    50 30 20
	 // or
	 //    10 20 20
bool isIn(const double a1[], int n1, const double a2[], int n2)
{
	if (n2 <= 0 || n1>n2)
	{
		return false;
	}
	
	if (n1 <= 0)
		return true;

	if (a1[0] == a2[0])
		return isIn(a1 + 1, n1 - 1, a2 + 1, n2 - 1);
	else
	{
		return isIn(a1+1, n1-1, a2 , n2 );
	}
	
}

int main()
{
	double a2[] = { 10, 50, 40, 20, 50, 40, 30 };
	double a11[] = { 50, 20, 30 };
	assert(isIn(a11, 3, a2, 7) == true);
	double a12[] = { 50, 40, 40 };
	assert(isIn(a12, 3, a2, 7) == true);
	double a13[] = { 50, 30, 20 };
	assert(isIn(a13, 3, a2, 7) == false);
	double a14[] = { 10, 20, 20 };
	assert(isIn(a14, 3, a2, 7) == false);
	assert(isIn(a14, 0, a2, 7) == true);
	double a15[] = { 10, 50, 40 };
	assert(isIn(a15, 3, a2, 7) == true);
	assert(isIn(a15, 3, a2, 3) == true);
	assert(isIn(a15, 3, a2, 2) == false);
	assert(isIn(a15, 3, a2, 7) == true);
	assert(isIn(a15, 0, a2, 0) == true);
	assert(isIn(a15, -1, a2, 0) == true);
	assert(isIn(a15, -1, a2, 1) == true);
	assert(isIn(a15, 1, a2, 0) == false);
	assert(isIn(a15, 0, a2, -1) == true);
}