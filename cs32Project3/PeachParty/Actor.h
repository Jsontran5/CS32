#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"


// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class Actor : public GraphObject
{
public:
	Actor(int imageID, int startX, int startY, StudentWorld* myWorld, int dir = right, int depth = 0, double size = 1.0);
	virtual ~Actor() {};

	virtual void doSomething() = 0;


private:
	StudentWorld* m_world;
};

class Player : public Actor
{
public:
	Player(int imageID, int startX, int startY, StudentWorld* myWorld, int dir = right, int depth = 0, double size = 1.0);


};



class Bowser : public Actor // or some subclass of Actor
{
public:
	
};


class CoinSquare : public Actor // or some subclass of Actor //SQUARES BASICALLY AFFECT THE PLAYER function
{
public:
	CoinSquare(int imageID, int startX, int startY, StudentWorld* myWorld, int dir = right, int depth = 0, double size = 1.0);

	//doSomething
};



#endif // ACTOR_H_
