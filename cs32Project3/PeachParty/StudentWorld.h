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

  
  void spawnVortex(int x, int y, int dir);

  Player* getPeach() const { return m_peach; }
  Player* getYoshi() const { return m_yoshi; }


  // Determine if there is a square at the specified location. Used to determine if a gameobject
  // like a player, enemy or vortex can move onto the specified location
  bool is_there_a_square_at_location(int dest_x, int dest_y) const;

  // Get a pointer to the square at the specified location
  Actor* get_square_at_location(int x, int y) const;

  // get # of coins in the bank
  int get_bank_coins() const {return m_bank;}

  // add coins to the bank (when player passes over a bank square)
  void deposit_bank_coins(int coins) { m_bank += coins; }

  // reset # of coins in the bank to zero
  void reset_bank_coins() {m_bank = 0;}

  // Given a player object pointer, returns a pointer to the other player object. Used for swapping
  // actions.
  Player* get_other_player(int pNum) const;


private:
	std::vector<Actor*> actors;
	Player* m_peach;
	Player* m_yoshi;
	int m_bank;

	

};

#endif // STUDENTWORLD_H_
