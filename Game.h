// Game.h
// Elijah Willis

#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include <stdio.h>

class Temple;

class Game
{
public:
    Game(int goblinSmellDistance);
    void play();
    ~Game();

private:
    Temple* m_temple;


};

#endif // GAME_INCLUDED
