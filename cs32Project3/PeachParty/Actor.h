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

	virtual bool is_a_square() const = 0; 
	virtual bool can_be_hit_by_vortex() const = 0;
	virtual bool alter_Dir() { return false; }
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
	bool is_waitAction() const { return m_waitAction; }
	bool is_firstMove() const { return m_firstMove; }
	

	int get_dice() const { return m_roll; }    // used to display stats on status line
	int get_stars() const { return m_stars; }   // used to display stats on status line
	int get_coins() const { return m_coins; }
	bool has_vortex() const { return m_vortex; }
	int get_ticks() const { return m_ticksToMove; }
	int get_walkDir() const {return m_walkDir;}
	int get_roll() const { return m_roll; }

	bool is_a_square() const { return false; }
	bool can_be_hit_by_vortex() const { return false; }
	void hit_by_vortex() { return; };
	bool validDir(int x, int y, int dir);
	bool on_fork();
	void force_walk_direction(int angle);


	void randomDir();
	void teleport_me_to_random_sq();
	void adjust_stars(const int this_much) { m_stars += this_much; return; }
	void adjust_coins(const int this_much) { m_coins += this_much; return; }

	void adjust_action(bool action) { m_waitAction = action; }

	void adjust_walkDir(int dir) { m_walkDir = dir; }
	void adjust_vortex(bool ammo) { m_vortex = ammo; }
	void adjust_ticks(int tick) { m_ticksToMove = tick; }
	void adjust_rolls(int roll) { m_roll = roll; }
	void adjust_waitingRoll(bool state) { m_waitingRoll = state; }
	void adjust_teleState(bool tele) { m_teleported = tele; }


private:

	int  m_playerNum;
	int m_walkDir;
	int m_ticksToMove;
	bool m_waitingRoll;
	int m_coins;
	int m_stars;
	int m_roll;
	bool m_vortex;
	bool m_waitAction;
	bool m_firstMove;
	bool m_teleported;
	
};


class ActivatingObject : public Actor {
public:
	ActivatingObject(StudentWorld* myWorld, int imageID, int startX, int startY, int dir = right, int depth = 1)
		: Actor(myWorld, imageID, startX, startY, dir, depth) {};


  void doSomething() { return; }
};

class ActivateOnPlayer : public ActivatingObject {
public:
	ActivateOnPlayer(StudentWorld* myWorld, int imageID, int startX, int startY, int dir = right, int depth = 1, bool activate_when_go_lands = true)
		:ActivatingObject(myWorld, imageID, startX, startY, dir, depth) {};
};

class Vortex : public ActivatingObject {
public:
  Vortex(StudentWorld* myWorld, int imageID, int startX, int startY, int dir)
	  :ActivatingObject(myWorld, imageID, startX, startY, dir) {};

  bool is_a_square() const { return false; }
  bool can_be_hit_by_vortex() const { return false; }

  std::vector<Actor*> do_i_activate();

  void doSomething() { return; }
};

class StarSquare : public ActivateOnPlayer { //CHECK DEPTH
public:
	StarSquare(StudentWorld* myWorld, int imageID, int startX, int startY)
		:ActivateOnPlayer(myWorld, imageID, startX, startY) {};


	bool is_a_square() const { return true; }
	bool can_be_hit_by_vortex() const { return false; }


	void doSomething();
};

class CoinSquare : public ActivateOnPlayer {
public:
  CoinSquare(StudentWorld* myWorld, int imageID, int startX, int startY, int adjust_coins_by)
	  :ActivateOnPlayer(myWorld, imageID, startX, startY) {
	  m_coinAdjust = adjust_coins_by;
  }
  
  
  bool is_a_square() const { return true; }
  bool can_be_hit_by_vortex() const { return false; }

  void doSomething();

private:
	int m_coinAdjust;
};

class DirectionalSquare : public ActivateOnPlayer {
public:
  DirectionalSquare(StudentWorld* myWorld, int imageID, int startX, int startY, int dir, int angle)
	  :ActivateOnPlayer(myWorld, imageID, startX, startY, dir) 
  {
	
	  m_angle = angle;
  }


  bool alter_Dir() { return true; }
  bool is_a_square() const { return true; }
  bool can_be_hit_by_vortex() const { return false; }
  int get_angle() { return m_angle; }


  void doSomething();

private:
	int m_angle;
};

class BankSquare : public ActivateOnPlayer {
public:
  BankSquare(StudentWorld* myWorld, int imageID, int startX, int startY)
	  :ActivateOnPlayer(myWorld, imageID, startX, startY) {};


  bool is_a_square()const { return true; }
  bool can_be_hit_by_vortex() const { return false; }

  void doSomething();
};

class EventSquare : public ActivateOnPlayer {
public:
  EventSquare(StudentWorld* myWorld, int imageID, int startX, int startY)
	  :ActivateOnPlayer(myWorld, imageID, startX, startY) {};

  bool is_a_square() const { return true; }
  bool can_be_hit_by_vortex() const { return false; }

  void doSomething();
};

class Enemy : public ActivateOnPlayer {
public:
  Enemy(StudentWorld* myWorld, int imageID, int startX, int startY, int num_sq_to_move=0, int number_of_ticks_to_pause=0, bool activate_when_go_lands=true, int dir = right
	  ,int depth = 0):ActivateOnPlayer(myWorld, imageID, startX, startY, dir, depth) {};

  void doSomething() { return; }

  bool is_a_square() const { return false; }
  bool can_be_hit_by_vortex()const { return true; }

  void hit_by_vortex();  // called when enemy is hit by a vortex projectile (called by vortex projectile)
};

class DroppingSquare : public ActivateOnPlayer {
public:
  DroppingSquare(StudentWorld* myWorld, int imageID, int startX, int startY)
	  :ActivateOnPlayer(myWorld, imageID, startX, startY) {};

  bool is_a_square() const { return true; }
  bool can_be_hit_by_vortex()const { return false; }


  void doSomething();
};

class Bowser : public Enemy {
public:
	Bowser(StudentWorld* myWorld, int imageID, int startX, int startY)
		:Enemy(myWorld, imageID, startX, startY) {};


	void doSomething() { return; };
};

class Boo : public Enemy {
public:
  Boo(StudentWorld* myWorld, int imageID, int startX, int startY)
	  :Enemy(myWorld, imageID, startX, startY) {};
};

#endif

