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
	m_walkDir = right;
	 m_ticksToMove = 0;
	 m_waitingRoll= true;
}

void Player::doSomething()
{
	if (m_waitingRoll)
	{
		int action = getWorld()->getAction(1); //hard coded for peach
		if (action == ACTION_ROLL)
		{
			int die_roll = randInt(1, 10);
			std::cout << die_roll << std::endl;
			m_ticksToMove = die_roll * 8;
			m_waitingRoll = false;
		}
		else
		{
			return;
		}
	}
	else
	{
		int newX;
		int newY;

		getPositionInThisDirection(m_walkDir, SPRITE_WIDTH, newX, newY);

		if (getWorld()->isValidPos(newX, newY, m_walkDir))
		{
			switch (m_walkDir)
			{
			case right:
				moveTo(getX() + 2, getY());
				break;
			case left:
				moveTo(getX() - 2, getY());
				break;
			case up:
				moveTo(getX(), getY() + 2);
				break;
			case down:
				moveTo(getX(), getY() - 2);
				break;
			}

			m_ticksToMove--;
		}
		else
		{
			if (m_walkDir == right || m_walkDir == left)
			{
				getPositionInThisDirection(up, SPRITE_WIDTH, newX, newY); 
				if (getWorld()->isValidPos(newX, newY, up))
				{
					m_walkDir = up;
					setDirection(right);
					moveAtAngle(up, 2);
					m_ticksToMove--;
				}
				else
				{
					m_walkDir = down;
					setDirection(right);
					moveAtAngle(down, 2);
					m_ticksToMove--;
				}
			}
			else if (m_walkDir == up || m_walkDir == down)
			{

				getPositionInThisDirection(right, SPRITE_WIDTH, newX, newY);
				if (getWorld()->isValidPos(newX, newY, right))
				{
					m_walkDir = right;
					setDirection(right);
					moveAtAngle(right, 2);
					m_ticksToMove--;
				}
				else
				{
					m_walkDir = left;
					setDirection(left);
					moveAtAngle(left, 2);
					m_ticksToMove--;
				}
			}

		}
		if (m_ticksToMove <= 0)
		{
			m_waitingRoll = true;
		}

	}
	

}

//CoinSquare Implementation
CoinSquare::CoinSquare(StudentWorld* myWorld, int imageID, int startX, int startY, int dir, int depth)
	:Actor(myWorld, imageID, startX, startY,  dir, depth)
{
	m_giveCoin = true;
}

void CoinSquare::doSomething()
{
	if (!isAlive())
	{
		return;
	}
	return;
}