#ifndef GAME_INCLUDED
#define GAME_INCLUDED


#include <string>
class Arena;

using namespace std;

class Game
{
public:
    // Constructor/destructor
    Game(int rows, int cols, int nRabbits);
    ~Game();

    // Mutators
    void play();

private:
    Arena* m_arena;

    // Helper functions
    string takePlayerTurn();
};


#endif
