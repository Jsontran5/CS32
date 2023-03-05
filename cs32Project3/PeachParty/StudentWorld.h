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

  bool isValidPos(int x, int y, int dir);
  bool isFork(int x, int y, int dir);

  Player* getPeach() const { return m_peach; }
  Player* getYoshi() const { return m_yoshi; }

private:
	std::vector<Actor*> actors;
	Player* m_peach;
	Player* m_yoshi;
	int m_bank;

	

};

#endif // STUDENTWORLD_H_
