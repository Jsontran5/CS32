#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
#include <sstream>
#include "Actor.h"
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
}

int StudentWorld::init() //work on this first
{
    Board bd;
    int boardNum = getBoardNumber();
    ostringstream oss;
    oss << "board0" << boardNum << ".txt";

    string board_file = assetPath() + oss.str();
    Board::LoadResult result = bd.loadBoard(board_file);
    if (result == Board::load_fail_file_not_found)
        cerr << "Could not find board01.txt data file\n";
    else if (result == Board::load_fail_bad_format)
        cerr << "Your board was improperly formatted\n";
    else if (result == Board::load_success) {
        cerr << "Successfully loaded board\n";

        for (int i = 0; i < BOARD_WIDTH; i++)
        {
            for (int j = 0; j < BOARD_HEIGHT; j++)
            {
                Board::GridEntry ge = bd.getContentsOf(i, j);
                switch (ge) {
                case Board::empty:

                    break;
                case Board::boo:

                    break;
                case Board::bowser:


                    break;
                case Board::player:
                    m_peach = new Player(this, IID_PEACH, i * SPRITE_WIDTH, j * SPRITE_HEIGHT); //added in PEACH
                    actors.push_back(new CoinSquare(this, IID_BLUE_COIN_SQUARE, i * SPRITE_WIDTH, j * SPRITE_HEIGHT));
                    break;
                case Board::red_coin_square:

                    break;
                case Board::blue_coin_square:
                    actors.push_back(new CoinSquare(this, IID_BLUE_COIN_SQUARE, i * SPRITE_WIDTH, j * SPRITE_HEIGHT));


                    break;
                }
            }

        }
        return GWSTATUS_CONTINUE_GAME;
    }
}

int StudentWorld::move()
{
    m_peach->doSomething(); //add for yoshi later

    for (int i = 0; i < actors.size(); i++)
    {
        actors[i]->doSomething();
    }

    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    delete m_peach; //add for yoshi later

    for (int i = 0; i < actors.size(); i++)
    {
        delete actors[i];
    }

}
