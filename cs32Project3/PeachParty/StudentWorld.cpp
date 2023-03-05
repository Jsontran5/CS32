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
    m_bank = 0;
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
                case Board::boo: //add i nthe baddies
                    actors.push_back(new Boo(this, IID_BOO, i * SPRITE_WIDTH, j * SPRITE_HEIGHT));
                    actors.push_back(new CoinSquare(this, IID_BLUE_COIN_SQUARE, i * SPRITE_WIDTH, j * SPRITE_HEIGHT));
                    break;
                case Board::bowser:
                    actors.push_back(new Bowser(this, IID_BOWSER, i * SPRITE_WIDTH, j * SPRITE_HEIGHT));
                    actors.push_back(new CoinSquare(this, IID_BLUE_COIN_SQUARE, i * SPRITE_WIDTH, j * SPRITE_HEIGHT));
                    break;
                case Board::player:

                    m_peach = new Player(this, IID_PEACH, i * SPRITE_WIDTH, j * SPRITE_HEIGHT, 1); 
                    m_yoshi = new Player(this, IID_YOSHI, i * SPRITE_WIDTH, j * SPRITE_HEIGHT, 2);

                    actors.push_back(new CoinSquare(this, IID_BLUE_COIN_SQUARE, i * SPRITE_WIDTH, j * SPRITE_HEIGHT));
                    break;
                case Board::red_coin_square:
                    actors.push_back(new CoinSquare(this, IID_RED_COIN_SQUARE, i * SPRITE_WIDTH, j * SPRITE_HEIGHT, -3));
                    break;
                case Board::blue_coin_square:
                    actors.push_back(new CoinSquare(this, IID_BLUE_COIN_SQUARE, i * SPRITE_WIDTH, j * SPRITE_HEIGHT));
                    break;
                case Board::up_dir_square:
                    actors.push_back(new DirectionalSquare(this, IID_DIR_SQUARE, i * SPRITE_WIDTH, j * SPRITE_HEIGHT, 90, 90)); //SPRITE OF DIRECTIONAL SQUARE CURRENTLY WRONG
                    break;
                case Board::down_dir_square:
                    actors.push_back(new DirectionalSquare(this, IID_DIR_SQUARE, i * SPRITE_WIDTH, j * SPRITE_HEIGHT, 270, 270));
                    break;
                case Board::left_dir_square:
                    actors.push_back(new DirectionalSquare(this, IID_DIR_SQUARE, i * SPRITE_WIDTH, j * SPRITE_HEIGHT, 180,180));
                    break;
                case Board::right_dir_square:
                    actors.push_back(new DirectionalSquare(this, IID_DIR_SQUARE, i * SPRITE_WIDTH, j * SPRITE_HEIGHT, 0,0));
                    break;
                case Board::event_square:
                    actors.push_back(new EventSquare(this, IID_EVENT_SQUARE, i * SPRITE_WIDTH, j * SPRITE_HEIGHT));
                    break;
                case Board::bank_square:
                    actors.push_back(new BankSquare(this, IID_BANK_SQUARE, i * SPRITE_WIDTH, j * SPRITE_HEIGHT));
                    break;
                case Board::star_square:
                    actors.push_back(new StarSquare(this, IID_STAR_SQUARE, i * SPRITE_WIDTH, j * SPRITE_HEIGHT));
                    break;
                }


            }

        }
    }

    startCountdownTimer(99);
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
  
        m_peach->doSomething();
    
        
        m_yoshi->doSomething();
    
  
    for (int i = 0; i < actors.size(); i++)
    {
        actors[i]->doSomething();
    }

    stringstream status;

    status << "P1 Roll: ";
    status << m_peach->get_dice();
    status << " Stars: ";
    status << m_peach->get_stars();
    status << " $$: ";
    status << m_peach->get_coins();
    
    if (m_peach->has_vortex())
    {
        status << " VOR ";
    }
    else
    {
        status << " ";
    }

    status << "| Time: ";
    status << timeRemaining();
    status << " | Bank: ";
    status << m_bank;

    status << " |P2 ROLL: ";
    status << m_yoshi->get_dice();
    status << " Stars: ";
    status << m_yoshi->get_stars();
    status << " $$: ";
    status << m_yoshi->get_coins();

    if (m_yoshi->has_vortex())
    {
        status << " VOR ";
    }
    else
    {
        status << " ";
    }
    setGameStatText(status.str());

    if (timeRemaining() == 0)
    {
        playSound(SOUND_GAME_FINISHED);

        int peachStars = m_peach->get_stars();
        int yoshiStars = m_yoshi->get_stars();

        int peachCoins = m_peach->get_coins();
        int yoshiCoins = m_yoshi->get_coins();
        if (peachStars > yoshiStars)
        {
            setFinalScore(peachStars, peachCoins);
            return GWSTATUS_PEACH_WON;
        }
        else if (peachStars < yoshiStars)
        {
            setFinalScore(yoshiStars, yoshiCoins);
            return GWSTATUS_YOSHI_WON;
        }
        else if (peachStars == yoshiStars)
        {
            if (peachCoins > yoshiCoins)
            {
                setFinalScore(peachStars, peachCoins);
                return GWSTATUS_PEACH_WON;
            }
            else if (peachCoins < yoshiCoins)
            {
                setFinalScore(yoshiStars, yoshiCoins);
                return GWSTATUS_YOSHI_WON;
            }
            else
            {
                int winner = randInt(1, 2);
                if (winner == 1)
                {
                    setFinalScore(peachStars, peachCoins);
                    return GWSTATUS_PEACH_WON;
                }
                else
                {
                    setFinalScore(yoshiStars, yoshiCoins);
                    return GWSTATUS_YOSHI_WON;
                }
                
            }
        }
    }
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    delete m_peach; //add for yoshi later
    m_peach = nullptr;
    delete m_yoshi;
    m_yoshi = nullptr;

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

   

    if (x < BOARD_WIDTH && x >= 0 && y < BOARD_HEIGHT && y >= 0)
    {
        if (bd.getContentsOf(x, y) != Board::empty)
            return true;
    }

    return false;
    //cout << "test1 " << x << " and1 " << y << endl;

    /*for (int i = 0; i < actors.size(); i++)
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

    }*/
    return false;
}

bool isFork(int x, int y, int dir)
{
    return false;
}