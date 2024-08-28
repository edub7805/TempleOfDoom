// Dragon.h
// Elijah Willis

#ifndef DRAGON_INCLUDED
#define DRAGON_INCLUDED

#include "Monster.h"
#include "Weapon.h"
#include "Scroll.h"
#include "utilities.h"

class Dragon: public Monster {
public:
    // Initializing the constructor
    Dragon(Temple* temple) : Monster(temple, 'D', "Dragon", randInt(6)+20, 4, 4, 4) {
        setTheWeapon(new LongSword(temple));
    }
    
    ~Dragon() {}
    
    // Handling movement decisions
    void calculateMove() {
        if (checkIsAsleep()) {
            return;
        }
        
        // Healing mechanism
        if (trueWithProbability(0.1)) {
            adjustTheHP(1);
        }
        
        // Engaging the player if nearby
        if (pathToPlayer() == 1) {
            hit(this, (Actor*)getTheTemple()->getMyPlayer());
        }
    }
    
    // Dropping items randomly
    GameObject* dropAGameObject() {
        if (!isOverGameObject()) {
            int random = randInt(5);
            if (random == 0) {
                return new TeleportationScroll(getTheTemple());
            } else if (random == 1) {
                return new HealthScroll(getTheTemple());
            } else if (random == 2) {
                return new ArmorScroll(getTheTemple());
            } else if (random == 3) {
                return new StrengthScroll(getTheTemple());
            } else if (random == 4) {
                return new DexterityScroll(getTheTemple());
            }
        }
        return nullptr;
    }
    
private:
    
};


#endif // DRAGON_INCLUDED
