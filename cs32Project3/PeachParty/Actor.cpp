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
	 m_waitAction = false;
	 m_coins = 0;
	 m_stars = 0;
	 m_vortex = false;
	 m_roll = 0;
	 m_firstMove = true;
}

void Player::doSomething()
{
	if (m_waitingRoll)
	{
		if (!validDir(getX(), getY(), m_walkDir) && m_teleported)
		{
			randomDir();
			m_teleported = false;
		}

		int action = getWorld()->getAction(m_playerNum);
		if (action == ACTION_ROLL)
		{
			m_waitingRoll = false;
			int die_roll = randInt(1, 10);
			m_roll = die_roll;
			
			m_ticksToMove = m_roll * 8;
			
			m_waitAction = true;
		}
		else if (action == ACTION_FIRE)
		{
			if (m_vortex)
			{
				int vX;
				int vY;
				getPositionInThisDirection(m_walkDir, SPRITE_WIDTH, vX, vY);

				getWorld()->spawnVortex(vX, vY, m_walkDir);

				getWorld()->playSound(SOUND_PLAYER_FIRE);

				adjust_vortex(false);
			}
			
		}
		else
		{
			return;
		}
	}
	else
	{
		Actor* curSquare = nullptr;

		if (getWorld()->is_there_a_square_at_location(getX(), getY()))
		{
			curSquare = getWorld()->get_square_at_location(getX(), getY());
		}
			

		if (curSquare != nullptr && curSquare->alter_Dir())
		{
			curSquare->doSomething();
		}
		else if (on_fork() && !m_firstMove)
		{
			int action1 = getWorld()->getAction(m_playerNum);
			int opposite_dir = (m_walkDir + 180) % 360;

			if (action1 == ACTION_UP)
			{
				if (validDir( getX(), getY(), up) && opposite_dir != up) 
				{
					m_walkDir = up;
					setDirection(right);
					
				}
				else
					return;
			}
			else if (action1 == ACTION_DOWN)
			{
				if (validDir(getX(), getY(), down) && opposite_dir != down)
				{
					m_walkDir = down;
					setDirection(right);
					
				}
				else
					return;
			}
			else if (action1 == ACTION_LEFT)
			{
				if (validDir(getX(), getY(), left) && opposite_dir != left) 
				{
					m_walkDir = left;
					setDirection(left);
				}
				else
					return;
			}
			else if (action1 == ACTION_RIGHT)
			{
				if (validDir(getX(), getY(), right) && opposite_dir != right)
				{
					m_walkDir = right;
					setDirection(right);
				}
				else
					return;
			}
			else
			{
				return;
			}
		}
		else if (!validDir(getX(), getY(), m_walkDir))
		{
			
			if (m_walkDir == right || m_walkDir == left)
			{
				
				if (validDir(getX(), getY(), up))
				{
					m_walkDir = up;
					setDirection(right);

				}
				else
				{
					m_walkDir = down;
					setDirection(right);
				}
			}
			else if (m_walkDir == up || m_walkDir == down)
			{

				
				if (validDir(getX(), getY(), right))
				{
					m_walkDir = right;
					setDirection(right);
				
				}
				else
				{
					m_walkDir = left;
					setDirection(left);
					
				}
			}
		}

		
		moveAtAngle(m_walkDir, SPRITE_WIDTH/8);

		m_firstMove = false;
		m_ticksToMove--;

		if (m_ticksToMove % 8 == 0)
			m_roll--;

		if (m_ticksToMove <= 0)
		{
			m_waitingRoll = true;
			m_roll = 0;
			m_waitAction = true;
		}

	}
	
	return;

}

bool Player::on_fork()
{
	int validDirections = 0;
	for (int i = 0; i < 4; i++)
	{
		int opposite_dir = (m_walkDir + 180) % 360;

		if (i * 90 != opposite_dir && validDir(getX(), getY(), i * 90))
		{
			if (i * 90 != m_walkDir)
			{
				validDirections++;
			}
			
		}
			
	}
	//
	if (getWorld()->is_there_a_square_at_location(getX(), getY()) && validDirections >= 1) //&& (m_ticksToMove % 8 == 0))
	{
		return true;
	}

	return false;
}

void Player::randomDir()
{
	int randomDir = randInt(0, 3) * 90;

	while (!validDir(getX(), getY(), m_walkDir))
	{
		randomDir = randInt(0, 3) * 90;
	}

	adjust_walkDir(randomDir);
	if (randomDir == left)
	{
		setDirection(left);
	}
	else
	{
		setDirection(right);
	}

	
}

bool Player::validDir(int x, int y, int dir)
{
	int newX;
	int newY;
	getPositionInThisDirection(dir, SPRITE_WIDTH, newX, newY);
	if (dir == 180 || dir == 270)
	{
		while (newX % 16 != 0)
		{
			newX++;
		}
		while (newY % 16 != 0)
		{
			newY++;
		}
	}
	else
	{
		while (newX % 16 != 0)
		{
			newX--;
		}
		while (newY % 16 != 0)
		{ 
			newY--;
		}
	}

	
	return getWorld()->is_there_a_square_at_location(newX, newY);
}

void Player::force_walk_direction(int angle)
{
	m_walkDir = angle;

	if (angle == left)
	{
		setDirection(left);
	}
}
void Player::teleport_me_to_random_sq()
{
	int newX = randInt(0, 15) * SPRITE_WIDTH;
	int newY = randInt(0, 15) * SPRITE_WIDTH;


	while (!getWorld()->is_there_a_square_at_location(newX, newY)) 
	{
		newX = randInt(0, 15) * SPRITE_WIDTH;
		newY = randInt(0, 15) * SPRITE_WIDTH;
	}

	moveTo(newX, newY);
}


//COINSQUARE IMPLEMENTATION
void CoinSquare::doSomething()
{
	if (!isAlive())
	{
		return;
	}
		
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
					getWorld()->getPeach()->adjust_coins(getWorld()->getPeach()->get_coins()*-1);
					getWorld()->playSound(SOUND_TAKE_COIN);
					getWorld()->getPeach()->adjust_action(false);
				}
				else
				{
					getWorld()->getPeach()->adjust_coins(m_coinAdjust);
					getWorld()->playSound(SOUND_TAKE_COIN);
					getWorld()->getPeach()->adjust_action(false);
				}
			}
	}

	if (getWorld()->getYoshi()->getX() == getX() && getWorld()->getYoshi()->getY() == getY() && getWorld()->getYoshi()->is_waitingRoll() && getWorld()->getYoshi()->is_waitAction())
	{
			if (m_coinAdjust >= 0)
			{
				getWorld()->getYoshi()->adjust_coins(m_coinAdjust);
				getWorld()->playSound(SOUND_GIVE_COIN);
				getWorld()->getYoshi()->adjust_action(false);
			}
			else
			{
				int negPeachCoins = getWorld()->getYoshi()->get_coins() - 3;
				if (negPeachCoins < 0)
				{
					getWorld()->getYoshi()->adjust_coins(getWorld()->getYoshi()->get_coins()*-1);
					getWorld()->playSound(SOUND_TAKE_COIN);
					getWorld()->getYoshi()->adjust_action(false);
				}
				else
				{
					getWorld()->getYoshi()->adjust_coins(m_coinAdjust);
					getWorld()->playSound(SOUND_TAKE_COIN);
					getWorld()->getYoshi()->adjust_action(false);
				}
			}
	}

		return;
	
	
}




//STARSQUARE implementaion

void StarSquare::doSomething()
{
	//landed
	if (getWorld()->getPeach()->getX() == getX() && getWorld()->getPeach()->getY() == getY() && getWorld()->getPeach()->is_waitingRoll() && getWorld()->getPeach()->is_waitAction())
	{
		if (getWorld()->getPeach()->get_coins() < 20)
		{
			return;
		}
		else
		{
			getWorld()->getPeach()->adjust_coins(-20);
			getWorld()->getPeach()->adjust_stars(1);
			getWorld()->playSound(SOUND_GIVE_STAR);
			getWorld()->getYoshi()->adjust_action(false);
		}
	}
	else if (getWorld()->getYoshi()->getX() == getX() && getWorld()->getYoshi()->getY() == getY() && getWorld()->getYoshi()->is_waitingRoll() && getWorld()->getYoshi()->is_waitAction())
	{
		if (getWorld()->getYoshi()->get_coins() < 20)
		{
			return;
		}
		else
		{
			getWorld()->getYoshi()->adjust_coins(-20);
			getWorld()->getYoshi()->adjust_stars(1);
			getWorld()->playSound(SOUND_GIVE_STAR);
			getWorld()->getYoshi()->adjust_action(false);
		}
	}
	else if (getWorld()->getPeach()->getX() == getX() && getWorld()->getPeach()->getY() == getY() && !getWorld()->getPeach()->is_waitingRoll() && getWorld()->getPeach()->is_waitAction())
	{
		if (getWorld()->getPeach()->get_coins() < 20)
		{
			return;
		}
		else
		{
			getWorld()->getPeach()->adjust_coins(-20);
			getWorld()->getPeach()->adjust_stars(1);
			getWorld()->playSound(SOUND_GIVE_STAR);
			getWorld()->getYoshi()->adjust_action(false);
		}
	}
	else if (getWorld()->getYoshi()->getX() == getX() && getWorld()->getYoshi()->getY() == getY() && !getWorld()->getYoshi()->is_waitingRoll() && getWorld()->getYoshi()->is_waitAction())
	{
		if (getWorld()->getYoshi()->get_coins() < 20)
		{
			return;
		}
		else
		{
			getWorld()->getYoshi()->adjust_coins(-20);
			getWorld()->getYoshi()->adjust_stars(1);
			getWorld()->playSound(SOUND_GIVE_STAR);
			getWorld()->getYoshi()->adjust_action(false);
		}
	}

}

//banksquare implementation
void BankSquare::doSomething()
{
	if (getWorld()->getPeach()->getX() == getX() && getWorld()->getPeach()->getY() == getY() && getWorld()->getPeach()->is_waitingRoll() && getWorld()->getPeach()->is_waitAction())
	{
		int m_coingive = getWorld()->get_bank_coins();
		getWorld()->getPeach()->adjust_coins(m_coingive);
		getWorld()->reset_bank_coins();
		getWorld()->playSound(SOUND_WITHDRAW_BANK);
		getWorld()->getPeach()->adjust_action(false);
	}
	else if (getWorld()->getYoshi()->getX() == getX() && getWorld()->getYoshi()->getY() == getY() && getWorld()->getYoshi()->is_waitingRoll() && getWorld()->getYoshi()->is_waitAction())
	{
		int m_coingive = getWorld()->get_bank_coins();
		getWorld()->getYoshi()->adjust_coins(m_coingive);
		getWorld()->reset_bank_coins();
		getWorld()->playSound(SOUND_WITHDRAW_BANK);
		getWorld()->getYoshi()->adjust_action(false);
	}
	else if (getWorld()->getPeach()->getX() == getX() && getWorld()->getPeach()->getY() == getY() && !getWorld()->getPeach()->is_waitingRoll())
	{
		if (getWorld()->getPeach()->get_coins() - 5 < 0)
		{
			getWorld()->deposit_bank_coins(getWorld()->getPeach()->get_coins());
			getWorld()->getPeach()->adjust_coins(-1* getWorld()->getPeach()->get_coins());
			getWorld()->playSound(SOUND_DEPOSIT_BANK);

		}
		else
		{
			getWorld()->deposit_bank_coins(5);
			getWorld()->getPeach()->adjust_coins(-5);
			getWorld()->playSound(SOUND_DEPOSIT_BANK);
		}
	}
	else if (getWorld()->getYoshi()->getX() == getX() && getWorld()->getYoshi()->getY() == getY() && !getWorld()->getYoshi()->is_waitingRoll())
	{
		if (getWorld()->getYoshi()->get_coins() - 5 < 0)
		{
			getWorld()->deposit_bank_coins(getWorld()->getYoshi()->get_coins());
			getWorld()->getYoshi()->adjust_coins(-1 * getWorld()->getYoshi()->get_coins());
			getWorld()->playSound(SOUND_DEPOSIT_BANK);

		}
		else
		{
			getWorld()->deposit_bank_coins(5);
			getWorld()->getYoshi()->adjust_coins(-5);
			getWorld()->playSound(SOUND_DEPOSIT_BANK);
		}
	}
}

//eventsquare implementation
void EventSquare::doSomething()
{
	int event = randInt(1, 3);
	if (getWorld()->getPeach()->getX() == getX() && getWorld()->getPeach()->getY() == getY() && getWorld()->getPeach()->is_waitingRoll() && getWorld()->getPeach()->is_waitAction())
	{
		if (event == 1)
		{
			getWorld()->playSound(SOUND_PLAYER_TELEPORT);

			getWorld()->getPeach()->teleport_me_to_random_sq();
		}
		else if (event == 2)
		{
			Player* player = getWorld()->getPeach();
			Player* other = getWorld()->get_other_player(1); //swap for yoshi

			int other_x = other->getX();
			int other_y = other->getY();
			int player_x = player->getX();
			int player_y = player->getY();

			player->moveTo(other_x, other_y);
			other->moveTo(player_x, player_y);

			int other_ticks = other->get_ticks();
			int player_ticks = player->get_ticks();

			player->adjust_ticks(other_ticks);
			other->adjust_ticks(player_ticks);

			int other_walk = other->get_walkDir();
			int player_walk= player->get_walkDir();

			player->adjust_walkDir(other_walk);
			other->adjust_walkDir(player_walk);

			int other_sprite = other->getDirection();
			int player_sprite = player->getDirection();

			player->setDirection(other_sprite);
			other->setDirection(player_sprite);

			int other_roll = other->get_roll();
			int player_roll = player->get_roll();

			player->adjust_rolls(other_roll);
			other->adjust_rolls(player_roll);

			bool other_waitRoll = other->is_waitingRoll();
			bool player_waitRoll = player->is_waitingRoll();

			player->adjust_waitingRoll(other_waitRoll);
			other->adjust_waitingRoll(player_waitRoll);

			player->adjust_teleState(true);
			other->adjust_teleState(true);
			other->adjust_action(false);
		}
		else if (event == 3)
		{
			if (!getWorld()->getPeach()->has_vortex())
			{
				getWorld()->getPeach()->adjust_vortex(true);
				getWorld()->playSound(SOUND_GIVE_VORTEX);
			}
		}

	}
	else if (getWorld()->getYoshi()->getX() == getX() && getWorld()->getYoshi()->getY() == getY() && getWorld()->getYoshi()->is_waitingRoll() && getWorld()->getYoshi()->is_waitAction())
	{
		if (event == 1)
		{
			getWorld()->playSound(SOUND_PLAYER_TELEPORT);

			getWorld()->getYoshi()->teleport_me_to_random_sq();
		}
		else if (event == 2)
		{
			Player* player = getWorld()->getYoshi();
			Player* other = getWorld()->get_other_player(2); //swap for yoshi

			int other_x = other->getX();
			int other_y = other->getY();
			int player_x = player->getX();
			int player_y = player->getY();

			player->moveTo(other_x, other_y);
			other->moveTo(player_x, player_y);

			int other_ticks = other->get_ticks();
			int player_ticks = player->get_ticks();

			player->adjust_ticks(other_ticks);
			other->adjust_ticks(player_ticks);

			int other_walk = other->get_walkDir();
			int player_walk = player->get_walkDir();

			player->adjust_walkDir(other_walk);
			other->adjust_walkDir(player_walk);

			int other_sprite = other->getDirection();
			int player_sprite = player->getDirection();

			player->setDirection(other_sprite);
			other->setDirection(player_sprite);

			int other_roll = other->get_roll();
			int player_roll = player->get_roll();

			player->adjust_rolls(other_roll);
			other->adjust_rolls(player_roll);

			bool other_waitRoll = other->is_waitingRoll();
			bool player_waitRoll = player->is_waitingRoll();

			player->adjust_waitingRoll(other_waitRoll);
			other->adjust_waitingRoll(player_waitRoll);

			player->adjust_teleState(true);
			other->adjust_teleState(true);
			other->adjust_action(false);

		}
		else if (event == 3)
		{
			if (!getWorld()->getYoshi()->has_vortex())
			{
				getWorld()->getYoshi()->adjust_vortex(true);
				getWorld()->playSound(SOUND_GIVE_VORTEX);
			}
		}
	}
}

//DirectionalSquare implementaion
void DirectionalSquare::doSomething()
{
	if (getWorld()->getPeach()->getX() == getX() && getWorld()->getPeach()->getY() == getY())// && getWorld()->getPeach()->is_waitingRoll() && getWorld()->getPeach()->is_waitAction())
	{
		getWorld()->getPeach()->force_walk_direction(m_angle);

	
	}

	if (getWorld()->getYoshi()->getX() == getX() && getWorld()->getYoshi()->getY() == getY())// && getWorld()->getYoshi()->is_waitingRoll() && getWorld()->getYoshi()->is_waitAction())
	{
		getWorld()->getYoshi()->force_walk_direction(m_angle);
	}

}