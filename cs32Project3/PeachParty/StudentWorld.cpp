#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
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
        string board_file = assetPath() + "board01.txt";
        Board::LoadResult result = bd.loadBoard(board_file);
        if (result == Board::load_fail_file_not_found)
            cerr << "Could not find board01.txt data file\n";
        else if (result == Board::load_fail_bad_format)
            cerr << "Your board was improperly formatted\n";
        else if (result == Board::load_success) {
            cerr << "Successfully loaded board\n";

            for (int i = 0; i < BOARD_HEIGHT; i++)
            {
                for (int j = 0; j < BOARD_WIDTH; j++)
                {
                    Board::GridEntry ge = bd.getContentsOf(i, j);
                    switch (ge) {
                    case Board::empty: //calling new for each, PEACH/blue coin square
                        cout << "Location 5,10 is empty\n";
                        break;
                    case Board::boo:
                        cout << "Location 5,10 has a Boo and a blue coin square\n";
                        break;
                    case Board::bowser:
                        
                            cout << "Location 5,10 has a Bowser and a blue coin square\n";
                        break;
                    case Board::player:
                        cout << "Location 5,10 has Peach & Yoshi and a blue coin square\n";
                        break;
                    case Board::red_coin_square:
                        cout << "Location 5,10 has a red coin square\n";
                        break;
                    case Board::blue_coin_square:
                        cout << "Location 5,10 has a blue coin square\n";
                        break;
                }
            }
           
        }



    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit ESC.
    // Notice that the return value GWSTATUS_NOT_IMPLEMENTED will cause our framework to end the game.

    setGameStatText("Game will end in a few seconds");
    
    /*if (timeRemaining() <= 0)
		return GWSTATUS_CONTINUE_GAME;*/
    
	return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
}
