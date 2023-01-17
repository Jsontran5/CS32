#include "History.h"

#include <iostream>
#include "globals.h"
using namespace std;


History::History(int nRows, int nCols)
{
    mRows = nRows;
    mCols = nCols;
    for (int r = 1; r <= mRows; r++)
    {
        for (int c = 1; c <= mCols; c++)
        {
            historyGrid[r - 1][c - 1] = 0;
        }

    }
 
}



bool History::record(int r, int c)
{
    if (r < 1 || c < 1 || r>mRows || r > mCols)
    {
        return false;
    }
    else
    {
        historyGrid[r - 1][c - 1] += 1;

        return true;
    }


   
}




void History::display() const
{
    clearScreen();

    char newGrid[MAXROWS][MAXCOLS];
  
  

    for (int r = 1; r <= mRows; r++)
    {
        for (int c = 1; c <= mCols; c++)
        {
            if (historyGrid[r - 1][c - 1] == 0)
            {
                newGrid[r - 1][c - 1] = '.';
                
            }
            else if (historyGrid[r - 1][c - 1] < 26 && historyGrid[r - 1][c - 1] != 0)
            {
                newGrid[r-1][c-1] = 'A' + historyGrid[r - 1][c - 1] - 1;
                
            }

        }// ifhistoryGrid[r - 1][c - 1] = '0'; //copy arena display
    }
    for (int r = 1; r <= mRows; r++)
    {
        for (int c = 1; c <= mCols; c++)
        {
            cout << newGrid[r-1][c-1];
        }
        cout << endl;
    }
       
}