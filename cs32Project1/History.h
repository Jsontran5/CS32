#ifndef HISTORY_INCLUDED
#define HISTORY_INCLUDED

#include "globals.h"

class History
{
public:
	History(int nRows, int nCols);
	bool record(int r, int c);
	void display() const;

private:

	int historyGrid[MAXROWS][MAXCOLS];
	int mRows;
	int mCols;

};


#endif