#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "StudentWorld.h"

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
	virtual void doSomething() {
		return;
	};

private:

	int m_ticksToMove;
	bool m_rollState;

};






class CoinSquare : public Actor // or some subclass of Actor //SQUARES BASICALLY AFFECT THE PLAYER function
{
public:
	CoinSquare(StudentWorld* myWorld, int imageID, int startX, int startY, int dir = right, int depth = 0);

	virtual void doSomething() {
		return;
	};

private:


};



#endif // ACTOR_H_
