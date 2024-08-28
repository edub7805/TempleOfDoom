//  Monster.h
// Elijah Willis

#ifndef Monster_h
#define Monster_h

#include <stdio.h>
#include "Actor.h"

class Monster: public Actor {
public:
  // Constructor
  Monster(Temple* temple, char symbol, string name, int hp, int armor, int strength, int dexterity);
  virtual ~Monster() {}
  
  // Actions
  virtual void calculateMove() = 0;
  void moveAttempt();
  int pathToPlayer();
  virtual GameObject* dropAGameObject() = 0;
  
private:
  // Helpers
  int rToP();
  int cToP();
};



#endif /* Monster_h */
