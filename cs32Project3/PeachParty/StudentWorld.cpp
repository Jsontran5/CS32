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
    ostringstream filename;
    filename << "board0" << boardNum << ".txt";

    string board_file = assetPath() + filename.str();
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
                    actors.push_back(new CoinSquare(this, IID_BLUE_COIN_SQUARE, i * SPRITE_WIDTH, j * SPRITE_HEIGHT));
                    break;
                case Board::bowser:

                    actors.push_back(new CoinSquare(this, IID_BLUE_COIN_SQUARE, i * SPRITE_WIDTH, j * SPRITE_HEIGHT));
                    break;
                case Board::player:
                    m_peach = new Player(this, IID_PEACH, i * SPRITE_WIDTH, j * SPRITE_HEIGHT); //added in PEACH
                    actors.push_back(new CoinSquare(this, IID_BLUE_COIN_SQUARE, i * SPRITE_WIDTH, j * SPRITE_HEIGHT));
                    break;
                case Board::red_coin_square:
                    actors.push_back(new CoinSquare(this, IID_RED_COIN_SQUARE, i * SPRITE_WIDTH, j * SPRITE_HEIGHT));
                    break;
                case Board::blue_coin_square:
                    actors.push_back(new CoinSquare(this, IID_BLUE_COIN_SQUARE, i * SPRITE_WIDTH, j * SPRITE_HEIGHT));
                    break;
                case Board::up_dir_square:
                    actors.push_back(new CoinSquare(this, IID_DIR_SQUARE, i * SPRITE_WIDTH, j * SPRITE_HEIGHT)); //SPRITE OF DIRECTIONAL SQUARE CURRENTLY WRONG
                    break;
                case Board::down_dir_square:
                    actors.push_back(new CoinSquare(this, IID_DIR_SQUARE, i * SPRITE_WIDTH, j * SPRITE_HEIGHT));
                    break;
                case Board::left_dir_square:
                    actors.push_back(new CoinSquare(this, IID_DIR_SQUARE, i * SPRITE_WIDTH, j * SPRITE_HEIGHT));
                    break;
                case Board::right_dir_square:
                    actors.push_back(new CoinSquare(this, IID_DIR_SQUARE, i * SPRITE_WIDTH, j * SPRITE_HEIGHT));
                    break;
                case Board::event_square:
                    actors.push_back(new CoinSquare(this, IID_EVENT_SQUARE, i * SPRITE_WIDTH, j * SPRITE_HEIGHT));
                    break;
                case Board::bank_square:
                    actors.push_back(new CoinSquare(this, IID_BANK_SQUARE, i * SPRITE_WIDTH, j * SPRITE_HEIGHT));
                    break;
                case Board::star_square:
                    actors.push_back(new CoinSquare(this, IID_STAR_SQUARE, i * SPRITE_WIDTH, j * SPRITE_HEIGHT));
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
    m_peach = nullptr;

    for (int i = 0; i < actors.size(); i++)
    {
        delete actors[i];
    }
    actors.clear();
}
bool StudentWorld::isValidPos(int x, int y, int dir)
{
    Board bd;
    int boardNum = getBoardNumber();
    ostringstream filename;
    filename << "board0" << boardNum << ".txt";
    string board_file = assetPath() + filename.str();
    Board::LoadResult result = bd.loadBoard(board_file);
    

   
    if (dir == 180 || dir == 270)
    {
        while (x % 16 != 0)
        {
            x++;
        }
        while (y % 16 != 0)
        {
            y++;
        }
    }
        
    
    
    x = x / 16;
    y = y / 16;

   

    /*if (x < BOARD_WIDTH && x >= 0 && y < BOARD_HEIGHT && y >= 0)
    {
        if (bd.getContentsOf(x, y) != Board::empty)
            return true;
    }*/

    //return false;
    //cout << "test1 " << x << " and1 " << y << endl;

    for (int i = 0; i < actors.size(); i++)
    {
        int squareX, squareY;
        squareX= actors[i]->getX() ;
        squareY = actors[i]->getY() ;

        
            while (squareX % 16 != 0)
            {
                squareX++;
            }
            while (squareY % 16 != 0)
            {
                squareY++;
            }
        

        squareX = squareX / 16;
        squareY = squareY / 16;
     

       

        if (x < BOARD_WIDTH && x >= 0 && y < BOARD_HEIGHT && y >= 0)
        {
            if (squareX == x && squareY == y )
            {
                
                
                    return true;
                
               
            }
        }
        else
        {
            return false;
        }

    }
    return false;
}