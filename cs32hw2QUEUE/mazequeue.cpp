#include <queue>
#include <iostream>
#include <string>
#include <cassert>

using namespace std;

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec);


class Coord
{
public:
    Coord(int r, int c) : m_row(r), m_col(c) {}
    int r() const { return m_row; }
    int c() const { return m_col; }
private:
    int m_row;
    int m_col;
};



// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise
bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
    queue<Coord> coordStack;

    Coord point(sr, sc);
    coordStack.push(point);
    maze[sr][sc] = '#';

    while (coordStack.empty() == false)
    {
        Coord current = coordStack.front();
        coordStack.pop();

        if (current.r() == er && current.c() == ec)
        {
            return true;
        }

        if (maze[current.r()][current.c() + 1] == '.') //east
        {
            Coord point(current.r(), current.c() + 1);
            coordStack.push(point);
            maze[current.r()][current.c() + 1] = '#';

        }
        if (maze[current.r() - 1][current.c()] == '.') //north
        {
            Coord point(current.r() - 1, current.c());
            coordStack.push(point);
            maze[current.r() - 1][current.c()] = '#';
        }
        if (maze[current.r()][current.c() - 1] == '.')//west
        {
            Coord point(current.r(), current.c() - 1);
            coordStack.push(point);
            maze[current.r()][current.c() - 1] = '#';
        }
        if (maze[current.r() + 1][current.c()] == '.')//south
        {
            Coord point(current.r() + 1, current.c());
            coordStack.push(point);
            maze[current.r() + 1][current.c()] = '#';
        }
    }
    return false;
}
int main() {
    string maze[10] = {
                 "XXXXXXXXXX",
                 "X..X...X.X",
                 "X.XXXX.X.X",
                 "X.X.X..X.X",
                 "X...X.XX.X",
                 "XXX......X",
                 "X.X.XXXX.X",
                 "X.XXX....X",
                 "X...X..X.X",
                 "XXXXXXXXXX"
    };

    if (pathExists(maze, 10, 10, 5, 3, 8, 8))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
}