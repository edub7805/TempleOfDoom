// Actor.cpp
// Elijah Willis

#include "Actor.h"
#include "Temple.h"
#include "Weapon.h"
#include "utilities.h"

const int PLAYER_STATISTICS = 99; // Max player statistics!

// Constructor implementation
Actor::Actor (Temple* temple, char symbol, string name, int hp, int armor, int strength, int dexterity): allObjects(temple, symbol, name), m_hp(hp),m_maxHP(hp), m_armor(armor), m_strength(strength), m_dexterity(dexterity), m_isAsleep(0), m_overGameObject(nullptr), m_weapon(nullptr) {}

// Destructor implementation
Actor::~Actor() {
    if (!isPlayer()) delete m_weapon;
}

// Accessor functions
int Actor::getTheHP() {
  return m_hp;
}

int Actor::getTheArmor() {
  return m_armor;
}

int Actor::getTheMaxHP() {
  return m_maxHP;
}

bool Actor::isOverGameObject() {
  return m_overGameObject != nullptr;
}

bool Actor::isAsleep() {
  return m_isAsleep > 0;
}


int Actor::getTheStrength() {
  return m_strength;
}

int Actor::getTheDexterity() {
  return m_dexterity;
}

Weapon* Actor::getWeapon() {
  return m_weapon;
}

GameObject* Actor::getOverTheGameObject() {
  return m_overGameObject;
}

// Mutator functions
void Actor::adjustTheHP(int x) { // Adjusting HP
    m_hp += x;

    if (m_hp >= 50) {
        m_hp = 50;
    }

    if (m_hp < 0) {
        m_hp = 0;
    }
}

void Actor::adjustSleepDuration(int x) { // Adjusting sleep duration
    if(m_isAsleep > 0 && x > 0) {
        m_isAsleep = max(m_isAsleep, x);
    } else {
        m_isAsleep += x;
    }
}

void Actor::adjustTheStrength(int x) { // Adjusting the strength
    m_strength = x;
    m_strength = (m_strength > PLAYER_STATISTICS ? PLAYER_STATISTICS : m_strength);
}

void Actor::adjustTheMaxHP(int x) { // Adjusting maxHP
    m_maxHP += x;
    if (m_maxHP > PLAYER_STATISTICS) {
        m_maxHP = PLAYER_STATISTICS;
    }
}


void Actor::adjustTheDexterity(int x) { // Adjusting dexterity
    m_dexterity += x;
    if (m_dexterity > PLAYER_STATISTICS) {
        m_dexterity = PLAYER_STATISTICS;
    }
}

void Actor::adjustTheArmor(int x) { // Adjusting armor
    m_armor += x;
    if (m_armor > PLAYER_STATISTICS) {
        m_armor = PLAYER_STATISTICS;
    }
}

void Actor::setTheWeapon(Weapon* weapon) {
  m_weapon = weapon;
}

void Actor::setOverAGameObject(GameObject* gameObject) {
  m_overGameObject = gameObject;
}


// Functions that allow for game interaction (move, attack, etc.)
void Actor::move(int cr, int cc, int nr, int nc) {
    // Check if the actor is currently over a GameObject and remove the association
    getTheTemple()->updateTheCurrentCell(this, cr, cc);
    if (isOverGameObject()) {
        setOverAGameObject(nullptr);
    }
  
    // Update the actor's position to the next cell
    setPosition(nr, nc);
  
    // Check if there is a GameObject in the next cell and associate the actor with it
    if (getTheTemple()->isThereGameObject(nr, nc)) {
        setOverAGameObject((GameObject*)getTheTemple()->getMyObject(nr, nc));
    }
  
    // Update the current and next cell in the dungeon to reflect the actor's movement
    getTheTemple()->updateTheNextCell(this, nr, nc);
    
}

void Actor::hit(Actor* a, Actor* d) { // a: attacker, d: defender
    // We must get attacker's weapon
    Weapon* attackerWeapon = a->getWeapon();
    
    // We must construct action string
    string actionString = a->getTheName() + " ";
    actionString += attackerWeapon->getActionString();
    actionString += " ";
    actionString += attackerWeapon->getTheName();
    actionString += " at ";
    actionString += d->getTheName();
    actionString += " and ";
    
    // We must determine if attacker hits
    bool h = isHit(a, d);
    
    // If attacker hits
    if (h) {
        // We must calculate damage points
        int damagePoints = randInt(a->getTheStrength() + attackerWeapon->getDamage());
        
        // We must inflict damage on defender
        d->adjustTheHP(-1 * damagePoints);
        
        // We must append damage information to action string
        actionString += "hits";
        
        // If attacker's weapon is "Magic Fangs" and there's a 20% chance
        if (attackerWeapon->getTheName() == "Magic Fangs" && trueWithProbability(0.2)) {
            // We must put defender to sleep for a random duration between 2 and 6 turns
            d->adjustSleepDuration(randInt(5)+2);
            // We must add message to indicate defender fell asleep due to magic fangs
            actionString += ", putting the " + d->getTheName() + " to sleep.";
        }
        
        // We must add action string to dungeon's list of actions
        getTheTemple()->addAction(actionString);
        
        // We must check if the defender is dead
        checkIsDead(d);
        
    } else { // If attacker misses
        // We must append "misses" message to action string
        actionString += "misses";
        // We must add action string to dungeon's list of actions
        getTheTemple()->addAction(actionString);
    }
}


bool Actor::isHit(Actor* a, Actor* d) {
    // We must calculate a's (the attacker's) points
    int attackerPoints = a->getTheDexterity() + a->getWeapon()->getDexBonus();
    
    // We must calculate d's (the defender's) points
    int defenderPoints = d->getTheDexterity() + d->getTheArmor();
    
    // randint will generate random number for each and that number will become deciding factor
    int AR = randInt(attackerPoints) + 1;
    int DR = randInt(defenderPoints) + 1;
    
    // the number generated will allow for hit outcome
    if (AR >= DR) {
        return true;
    } else {
        return false;
    }
}

void Actor::checkIsDead(Actor* a) {
    // We must check if actor's HP is 0
    if (a->getTheHP() == 0) {
        if (a->isMonster()) {
            // We must destroy monster from dungeon if monster is dead
            getTheTemple()->destroyTheMonster((Monster*)a);
        } else if (a->isPlayer()) {
            // We must end the game if player is dead
            getTheTemple()->endTheGame("You were defeated. Better luck next time!");
        }
    }
}

bool Actor::checkIsAsleep() {
    // We must check if actor is asleep
    if (isAsleep()) {
        // If asleep, we must add action and decrease sleep duration
        getTheTemple()->addAction("");
        adjustSleepDuration(-1);
        return true;
    }
    return false;
}


