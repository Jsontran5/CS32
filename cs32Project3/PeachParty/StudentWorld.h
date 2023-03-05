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
  
  void spawnVortex(int x, int y, int dir);

  Player* getPeach() const { return m_peach; }
  Player* getYoshi() const { return m_yoshi; }


  // Determine if there is a square at the specified location. Used to determine if a gameobject
  // like a player, enemy or vortex can move onto the specified location
  bool is_there_a_square_at_location(int dest_x, int dest_y) const;


private:
	std::vector<Actor*> actors;
	Player* m_peach;
	Player* m_yoshi;
	int m_bank;

	

};

#endif // STUDENTWORLD_H_
