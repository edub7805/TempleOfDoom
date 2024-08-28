// Bogeyman.h
// Elijah Willis

#ifndef BOGEYMAN_INCLUDED
#define BOGEYMAN_INCLUDED

#include <stdio.h>

#include "Monster.h"
#include "Weapon.h"
#include "utilities.h"


class Bogeyman: public Monster {
public:

  // Implementing the constructor
  Bogeyman(Temple* temple) : Monster(temple, 'B', "Bogeyman", randInt(6)+5, 2, randInt(2)+2, randInt(2)+2) {
    setTheWeapon(new ShortSword(temple));
  }

  ~Bogeyman() {}


  // ****************************** \\
  // ********** Actions *********** \\
  // ****************************** \\

  // We must define the action for calculating the move of the Bogeyman
  void calculateMove() {
    // If Bogeyman is asleep, do nothing
    if (checkIsAsleep()) {
      return;
    }

    // If next to Player, attack
    if (pathToPlayer() == 1) {
      hit(this, (Actor*)getTheTemple()->getMyPlayer());
    }
    // Else if within 5 steps from Player, attempt to move
    else if (pathToPlayer() <= 5) {
      moveAttempt();
    }
  }

  // We must define the action for randomly dropping a game object
GameObject* dropAGameObject() {
    // If not over a game object and with a certain probability, drop a Magic Axe
    if (!isOverGameObject() and trueWithProbability(0.1)) {
      return new MagicAxe(getTheTemple());
    }
    return nullptr;
  }
};

#endif // BOGEYMAN_INCLUDED


