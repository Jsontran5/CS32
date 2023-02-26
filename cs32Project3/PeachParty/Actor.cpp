#include "Actor.h"
#include "StudentWorld.h"


// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp 

//Actor implementation

Actor::Actor(StudentWorld* myWorld, int imageID, int startX, int startY, int dir, int depth)
:GraphObject(imageID, startX, startY, dir, depth)
{
	m_world = myWorld;
	m_isAlive = true;
}

bool Actor::isAlive()
{
	return m_isAlive;
}

StudentWorld* Actor::getWorld()
{
	return m_world;
}


//player implementation
Player::Player(StudentWorld* myWorld, int imageID, int startX, int startY, int dir, int depth)
	:Actor(myWorld, imageID, startX, startY,  dir, depth)
{
	 m_ticksToMove = 0;
	 m_rollState = false;
}



//CoinSquare Implementation
CoinSquare::CoinSquare(StudentWorld* myWorld, int imageID, int startX, int startY, int dir, int depth)
	:Actor(myWorld, imageID, startX, startY,  dir, depth)
{

}
