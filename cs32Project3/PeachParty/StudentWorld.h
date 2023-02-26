#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Board.h"
#include <vector>
#include <string>
#include "Actor.h"

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
  StudentWorld(std::string assetPath);
  ~StudentWorld() { cleanUp(); }
  virtual int init();
  virtual int move();
  virtual void cleanUp();

private:
	std::vector<Actor*> actors;
	Player* m_peach;

};

#endif // STUDENTWORLD_H_
