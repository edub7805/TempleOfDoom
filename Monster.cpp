// Monster.cpp
// Elijah Willis

#include "Monster.h"
#include "Player.h"  

// Implementing the constructor
Monster::Monster(Temple* temple, char symbol, string name, int hp, int armor, int strength, int dexterity) : Actor(temple, symbol, name, hp, armor, strength, dexterity) {}

int Monster::rToP() {
  // We must get the player's row position
  int pR = getTheTemple()->getMyPlayer()->getTheRowPosition();
  
  // We must return the difference between player's row and monster's row
  return pR - getTheRowPosition();
}

int Monster::cToP() {
  // We must get the player's column position 
  int pC = getTheTemple()->getMyPlayer()->getTheColPosition();
  
  // We must return the difference between player's column and monster's column
  return pC - getTheColPosition();
}

// Different action functions
void Monster::moveAttempt() {
  // We must get the current row and column positions
  int cr = getTheRowPosition();
  int cc = getTheColPosition();
  int nr = getTheRowPosition();
  int nc = getTheColPosition();
  
  // Determine direction to move
  if (rToP() > 0) {
    nr++;
  } else if (rToP() < 0) {
    nr--;
  }
  
  if (cToP() > 0) {
    nc++;
  } else if (cToP() < 0) {
    nc--;
  }
  
  // We must check if there's space or a game object in the new row position
  if (getTheTemple()->isThereSpace(nr, cc) || getTheTemple()->isThereGameObject(nr, cc)) {
    move(cr, cc, nr, cc);
  } else if (getTheTemple()->isThereSpace(cr, nc) || getTheTemple()->isThereGameObject(cr, nc)) {
    // Else move along column if possible
    move(cr, cc, cr, nc);
  }
}

int Monster::pathToPlayer() {
  // We must return the sum of the absolute differences between the row and column positions
  return abs(rToP()) + abs(cToP());
}
