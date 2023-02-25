#include "Actor.h"
#include "StudentWorld.h"


// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp 

Actor::Actor(int imageID, int startX, int startY, StudentWorld* myWorld, int dir = right, int depth = 0, double size = 1.0)
	: GraphObject(imageID, startX, startY, myWorld, dir, depth, size)
{
	m_world = myWorld;
}