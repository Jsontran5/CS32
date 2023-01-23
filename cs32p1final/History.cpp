#include "History.h"

#include <iostream>
#include "globals.h"
using namespace std;


History::History(int nRows, int nCols)
{
    mRows = nRows;
    mCols = nCols;
    for (int r = 0; r < mRows; r++)
    {
        for (int c = 0; c < mCols; c++)
        {
            historyGrid[r][c] = 0;
        }

    }
 
}



bool History::record(int r, int c)
{
    if (r < 1 || c < 1 || r>mRows || r > mCols)
    {
        return false;
    }
  
    historyGrid[r - 1][c - 1] += 1;
    return true;

}




void History::display() const
{
    clearScreen();

    char newGrid[MAXROWS][MAXCOLS];
  
  

    for (int r = 0; r < mRows; r++)
    {
        for (int c = 0; c < mCols; c++)
        {
            if (historyGrid[r][c] == 0)
            {
                newGrid[r][c] = '.';
                
            }
            else if (historyGrid[r][c] < 26 && historyGrid[r][c] != 0)
            {
                newGrid[r][c] = 'A' + historyGrid[r][c] - 1;
                
            }
            else
            {
                newGrid[r][c] = 'Z';
            }

        }//similar arena's display()
    }
    for (int r = 0; r < mRows; r++)
    {
        for (int c = 0; c < mCols; c++)
        {
            cout << newGrid[r][c];
        }
      
        cout << endl;
    }
    cout << endl;
}