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
	Player(StudentWorld* myWorld, int imageID, int startX, int startY, int dir = right, int depth = 0);

	virtual void doSomething();

private:

	int m_walkDir;
	int m_ticksToMove;
	bool m_waitingRoll;
	// CHECK IF PLAYER 1 or 2
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
