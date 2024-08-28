// Player.h
// Elijah Willis

#ifndef PLAYER_INCLUDED
#define PLAYER_INCLUDED

#include <stdio.h>
#include "Actor.h"

class GameObject;
class Weapon;
class Scroll;

class Player : public Actor {
public:
  // Constructor
  Player(Temple* temple);
  ~Player();
  
  // Actions
  void calculateAMove(char x);
  bool commitAnAction();
    bool  commitAnActionStair();
  void playAMove(int nr, int nc);
  void cheatMode();
    
    
  
  // Display
  void displayMyStats();
  void displayMyInventory();
    void displayMyInventoryW();
    void displayMyInventoryS();
  
private:
  bool                is_cheater;
  vector<GameObject*> m_inventory;
};


#endif // PLAYER_INCLUDED
