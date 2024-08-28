// Scroll.h
// Elijah Willis

#ifndef SCROLL_INCLUDED
#define SCROLL_INCLUDED

#include <stdio.h>
#include <string>
#include "GameObject.h"


class Scroll : public GameObject {
public:
  Scroll(Temple* temple, string name, string description, string actionString) : GameObject(temple, '?', name, description, actionString) {} // constructor
  
  virtual void activateScroll() = 0;
  
private:
  string m_actionString;
};


class TeleportationScroll : public Scroll {
public:
  TeleportationScroll(Temple* temple) : Scroll(temple, "Scroll of Teleportation", "This allows you to randomly place somewhere else on the level", "You feel your body wrenched in space and time.") {}
  
  // Moves player to a randomly generated position
  virtual void activateScroll() {
    Temple* temple = getTheTemple();
    Player*  player  = temple->getMyPlayer();
    int nr = -1;
    int nc = -1;
    
    temple->generateTheRandomPosition(player, nr, nc);
    player->move(player->getTheRowPosition(), player->getTheColPosition(), nr, nc);
  }
};


class HealthScroll : public Scroll {
public:
  HealthScroll(Temple* temple) : Scroll(temple, "Scroll of Health", "This increases your hit points", "You feel your heart beating stronger.") {}
  
  // Increases Player's MaxHP by random number
  virtual void activateScroll() {
    getTheTemple()->getMyPlayer()->adjustTheMaxHP(randInt(6)+3);
  }
};

class ArmorScroll : public Scroll {
public:
  ArmorScroll(Temple* temple) : Scroll(temple, "Scroll of Enhance Armor", "This increases your armor rating", "Your armor glows blue.") {}
  
  // Increase Player's Armor by random number
  virtual void activateScroll() {
    getTheTemple()->getMyPlayer()->adjustTheArmor(randInt(3)+1);
  }
};

class StrengthScroll : public Scroll {
public:
  StrengthScroll(Temple* temple) : Scroll(temple, "Scroll of Enhance Strength", "This increases your strength", "Your muscles bulge.") {}
  
  // Increases Player's Strength by random number
  virtual void activateScroll() {
    getTheTemple()->getMyPlayer()->adjustTheStrength(randInt(3)+1);
  }
};


class DexterityScroll : public Scroll {
public:
    DexterityScroll(Temple* temple) : Scroll(temple, "Scroll of Enhanced Dexterity", "This increases your dexterity rating", "You feel like less of a klutz.") {}
    
    // Increases Player's Dexterity by 1
    virtual void activateScroll() {
        getTheTemple()->getMyPlayer()->adjustTheDexterity(1);
    }
};

#endif /* Scroll_h */
