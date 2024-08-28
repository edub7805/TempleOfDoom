// Snakewoman.h
// Elijah Willis

#ifndef SNAKEWOMAN_INCLUDED
#define SNAKEWOMAN_INCLUDED

#include "Monster.h"
#include "Weapon.h"
#include "utilities.h"

const int SNAKEWOMAN_RANGE = 3;

class Snakewoman: public Monster {
public:
    // Constructor
    Snakewoman(Temple* temple) : Monster(temple, 'S', "Snakewoman", randInt(4)+3, 3, 2, 3) {
      setTheWeapon(new MagicFangs(temple));
    }

    ~Snakewoman() {}
    
 // Action functions
    void calculateMove() {
      if (checkIsAsleep()) {
        return;
      }
      
      if (pathToPlayer() == 1) {
        // If next to Player, attack
        hit(this, (Actor*)getTheTemple()->getMyPlayer());
      } else if (pathToPlayer() <= SNAKEWOMAN_RANGE) {
        // Else if 3 steps from Player, attemptMove
        moveAttempt();
      }
    }

GameObject* dropAGameObject() {
      if (!isOverGameObject() and trueWithProbability(0.3333)) {
        return new MagicFangs(getTheTemple());
      }
      return nullptr;
    }
};

#endif /* Snakewoman_h */
