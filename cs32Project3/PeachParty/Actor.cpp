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
Player::Player(StudentWorld* myWorld, int imageID, int startX, int startY, int playerNumber, int dir, int depth)
	:Actor(myWorld, imageID, startX, startY,  dir, depth)
{
	m_playerNum = playerNumber;
	m_walkDir = right;
	 m_ticksToMove = 0;
	 m_waitingRoll= true;
	 m_coins = 0;
	 m_stars = 0;
	 m_vortex = false;
	 m_roll = 0;
}

void Player::doSomething()
{
	if (m_waitingRoll)
	{
		int action = getWorld()->getAction(m_playerNum);
		if (action == ACTION_ROLL)
		{
			int die_roll = randInt(1, 10);
			m_roll = die_roll;
			//std::cout << die_roll << std::endl;
			m_ticksToMove = die_roll * 8;
			m_waitingRoll = false;
			m_waitAction = true;
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

//COINSQUARE IMPLEMENTATION
void CoinSquare::doSomething()
{
	if (isAlive())
	{
		if (getWorld()->getPeach()->getX() == getX() && getWorld()->getPeach()->getY() == getY() && getWorld()->getPeach()->is_waitingRoll() && getWorld()->getPeach()->is_waitAction())
		{
			if (m_coinAdjust >= 0)
			{
				getWorld()->getPeach()->adjust_coins(m_coinAdjust);
				getWorld()->playSound(SOUND_GIVE_COIN);
				getWorld()->getPeach()->adjust_action(false);
			}
			else
			{
				int negPeachCoins = getWorld()->getPeach()->get_coins() - 3;
				if (negPeachCoins < 0)
				{
					getWorld()->getPeach()->adjust_coins(getWorld()->getPeach()->get_coins() - getWorld()->getPeach()->get_coins());
					getWorld()->playSound(SOUND_TAKE_COIN);
					getWorld()->getPeach()->adjust_action(false);
				}
			}
		}

		if (getWorld()->getYoshi()->getX() == getX() && getWorld()->getYoshi()->getY() == getY() && getWorld()->getYoshi()->is_waitingRoll() && getWorld()->getYoshi()->is_waitAction())
		{
			if (m_coinAdjust >= 0)
			{
				getWorld()->getPeach()->adjust_coins(m_coinAdjust);
				getWorld()->playSound(SOUND_GIVE_COIN);
				getWorld()->getPeach()->adjust_action(false);
			}
			else
			{
				int negPeachCoins = getWorld()->getYoshi()->get_coins() - 3;
				if (negPeachCoins < 0)
				{
					getWorld()->getYoshi()->adjust_coins(getWorld()->getPeach()->get_coins() - getWorld()->getPeach()->get_coins());
					getWorld()->playSound(SOUND_TAKE_COIN);
					getWorld()->getYoshi()->adjust_action(false);
				}
			}
		}

		return;
	}
	else
	{
		return;
	}
}