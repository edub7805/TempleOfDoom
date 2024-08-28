// Weapon.h
// Elijah Willis

#ifndef WEAPON_INCLUDED
#define WEAPON_INCLUDED

#include <stdio.h>
#include <string>
#include "GameObject.h"

class Weapon : public GameObject {
    
public:
 // Constructor for Weapon, using second type of gameobject constructor
  Weapon(Temple* temple, string name, int damage, int dexBonus, string actionString) : GameObject(temple, ')', name, "Damage: +" + to_string(damage) + ", Dexterity: +" + to_string(dexBonus), actionString), m_damage(damage), m_dexBonus(dexBonus) {}
  
 // My accessor functions
  int getDamage() {
    return m_damage;
  }
  
  int getDexBonus() {
    return m_dexBonus;
  }
  
  virtual bool isMagicFangs() {
    return false;
  }
  
private:
  int    m_damage;
  int    m_dexBonus;
};

class ShortSword : public Weapon {
public:
  ShortSword(Temple* temple) : Weapon(temple, "Short Sword", 2, 0, "slashes") {}
};

class Mace : public Weapon {
public:
  Mace(Temple* temple) : Weapon(temple, "Mace", 2, 0, "swings") {}
};

class LongSword : public Weapon {
public:
  LongSword(Temple* temple) : Weapon(temple, "Long Sword", 4, 2, "swings") {}
};

class MagicAxe : public Weapon {
public:
  MagicAxe(Temple* temple) : Weapon(temple, "Magic Axe", 5, 5, "chops") {}
};

class MagicFangs : public Weapon {
public:
  MagicFangs(Temple* temple) : Weapon(temple, "Magic Fangs", 2, 3, "strikes") {}
  
  virtual bool isMagicFangs() {
    return true;
  }
};
#endif /* Weapon_h */
