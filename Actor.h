// Actor.h
// Elijah Willis


#ifndef ACTOR_INCLUDED
#define ACTOR_INCLUDED

#include <stdio.h>
#include "allObjects.h"

class Weapon;
class GameObject;

class Actor: public allObjects {
    
public:
    // Constructor
    Actor (Temple* temple, char symbol, string name, int hp, int armor, int strength, int dexterity);
    
    // Virtual Destructor
    virtual ~Actor();
    
    // Various accessors
    int getTheHP();
    int getTheArmor();
    int getTheStrength();
    int getTheDexterity();
    int getTheMaxHP();
    Weapon*     getWeapon();
    GameObject* getOverTheGameObject();
    
    // Boolean accessors
    bool isOverGameObject();
    bool isAsleep();
    
    // Various mutators
    void adjustTheHP(int x);
    void adjustTheMaxHP(int x);
    void adjustSleepDuration(int x);
    void hit(Actor* a, Actor* d);
    bool isHit(Actor* a, Actor* d);
    void checkIsDead(Actor* actor);
    bool checkIsAsleep();
    void setTheWeapon(Weapon* weapon);
    void setOverAGameObject(GameObject* gameObject);
    void adjustTheArmor(int x);
    void adjustTheStrength(int x);
    void adjustTheDexterity(int x);
    void move(int cr, int cc, int nr, int nc);

    
  private:
    GameObject* m_overGameObject;
    int m_hp;
    int m_maxHP;
    int m_strength;
    int m_dexterity;
    int m_armor;
    int m_isAsleep;
    Weapon*  m_weapon;
};

#endif // ACTOR_INCLUDED
