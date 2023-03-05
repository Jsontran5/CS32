#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

class StudentWorld;

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class Actor : public GraphObject
{
public:
	Actor(StudentWorld* myWorld, int imageID, int startX, int startY, int dir = right, int depth = 0);
	virtual ~Actor() {};

	bool isAlive();

	StudentWorld* getWorld();

	virtual void doSomething() = 0;


private:
	bool m_isAlive;
	StudentWorld* m_world;
};

class Player : public Actor
{
public:
	Player(StudentWorld* myWorld, int imageID, int startX, int startY, int playerNumber, int dir = right, int depth = 0);

	virtual void doSomething();
	bool is_waitingRoll() const { return m_waitingRoll; }
	int get_dice() const { return m_roll; }    // used to display stats on status line
	int get_stars() const { return m_stars; }   // used to display stats on status line
	int get_coins() const { return m_coins; }
	bool has_vortex() const { return m_vortex; }

private:

	int  m_playerNum;
	int m_walkDir;
	int m_ticksToMove;
	bool m_waitingRoll;
	int m_coins;
	int m_stars;
	int m_roll;
	bool m_vortex;
	
};






class CoinSquare : public Actor // or some subclass of Actor //SQUARES BASICALLY AFFECT THE PLAYER function
{
public:
	CoinSquare(StudentWorld* myWorld, int imageID, int startX, int startY, int dir = right, int depth = 1);

	virtual void doSomething();

private:
	bool m_giveCoin;

};



#endif // ACTOR_H_
