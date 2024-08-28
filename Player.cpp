// Player.cpp
// Elijah Willis

#include <iostream>
using namespace std;

#include "Player.h"
#include "Weapon.h"
#include "Scroll.h"
#include "utilities.h"

// Implementing the constructor
Player::Player(Temple* temple) : Actor(temple, '@', "Player", 20, 2, 2, 2), is_cheater(false) {
  Weapon* startWeapon = new ShortSword(temple);
  m_inventory.push_back(startWeapon);
  setTheWeapon(startWeapon);
}

Player::~Player() {
  // since all the player has is inventory, we need to essentially clear that
  while (!m_inventory.empty()) {
    allObjects* erase = m_inventory.back();
    m_inventory.pop_back();
    delete erase;
  }
}

void Player::calculateAMove(char input) {
  // If asleep, do nothing and end turn
  if (checkIsAsleep()) {
    return;
  }
  
  // Regain hit points
  if (trueWithProbability(0.1)) {
    adjustTheHP(1);
  }
  
  int cr = getTheRowPosition();
  int cc = getTheColPosition();
  int nr = cr;
  int nc = cc;
  
  // Determine next cell Player is trying to move
  switch (input) {
    case ARROW_LEFT:
      nc--;
      break;
    case ARROW_RIGHT:
      nc++;
      break;
    case ARROW_UP:
      nr--;
      break;
    case ARROW_DOWN:
      nr++;
      break;
  }
  
  // If next cell isWall, block Player
  if (getTheTemple()->isThereWall(nr, nc)) {
    getTheTemple()->addAction("");
  }
  
  // If next cell isSpace, move Player to space
  else if (getTheTemple()->isThereSpace(nr, nc)) {
    move(cr, cc, nr, nc);
    getTheTemple()->addAction("");
  }
  
  // If next cell isMonster, attack Monster
  else if (getTheTemple()->isThereMonster(nr, nc)) {
    hit(this, (Actor*)getTheTemple()->getMyObject(nr, nc));
  }
  
  // If next cell isGameObject, move Player onto GameObject
  else if (getTheTemple()->isThereGameObject(nr, nc)) {
    move(cr, cc, nr, nc);
  }
}


// Return true if item picked up to set didPlayerMove in Game.cpp

// Action Functions
bool Player::commitAnAction() {
    
    GameObject* gameObj = getOverTheGameObject();
    
    // If not over a GameObject, do nothing
    if (gameObj == nullptr) {
      getTheTemple()->addAction("");
      return true;
    }
    
    // If asleep, do nothing and end turn
    if (checkIsAsleep()) {
      return true;
    }

    // If over Golden Idol...
    if (gameObj->isGoldenIdol()) {
      getTheTemple()->endTheGame("You acquired the Golden Idol, you win!");
      return true;
    }
    
     // If over Stairs, descend Stairs to next level of temple
     if (getOverTheGameObject()->isStairs()) {
       getTheTemple()->addAction("");
       return true;
     }
     
     if (m_inventory.size() > 25) {
       getTheTemple()->addAction("Your inventory inventory is at its maximum capacity");
       return false;
     }
     
     // Else, GameObject is an item to be picked up
     m_inventory.push_back(gameObj);
     setOverAGameObject(nullptr);
     getTheTemple()->pickUpGameTheObject(gameObj);
     getTheTemple()->addAction("You picked up a " + gameObj->getTheName() + ".");
     return true;
    }

bool Player::commitAnActionStair() {
    
    GameObject* gameObj = getOverTheGameObject();
    
    // If not over a GameObject, do nothing
    if (gameObj == nullptr) {
      getTheTemple()->addAction("");
      return true;
    }
    
    // If asleep, do nothing and end turn
    if (checkIsAsleep()) {
      return true;
    }
    
    // If over Stairs, descend Stairs to next level of temple
    if (getOverTheGameObject()->isStairs()) {
        setOverAGameObject(nullptr);
        getTheTemple()->addAction("");
        getTheTemple()->nextLevel();
     }
     
     
     return true;
    }

void Player::cheatMode() {
    // We must set the player's current hit points to the cheat mode value
    adjustTheHP(50);
    // We must set the player's strength to the cheat mode value
    adjustTheStrength(9);

    // We must log the activation of cheat mode
    getTheTemple()->addAction("");
    
    // If in cheat mode, must now set to true
    is_cheater = true;
}

//
void Player::displayMyInventory() {
    // We must clear the screen before displaying the inventory
    clearScreen();
    
    // We must print the header for the inventory
    cout << "Inventory:" << endl;

    char letterInd = 'a';
    // We must iterate through the inventory to display each item
    for (int i = 0; i < m_inventory.size(); i++) {
        // We must print each item with its corresponding letter and description
        cout << (char)(letterInd + i) << ". " << m_inventory[i]->getTheName() << endl;
    }
    
    // We must prompt the player for input to equip a weapon, use a scroll, or exit the inventory
    
    char x = getCharacter();
    int inputIndex = x - letterInd;
    
    // We must check if the input is within the range of inventory slots
    if (inputIndex < m_inventory.size()) {
        if (m_inventory[inputIndex]->isWeapon()) {
            // We must equip the weapon if the item is a weapon
            setTheWeapon((Weapon*)m_inventory[inputIndex]);
            getTheTemple()->addAction("You are wielding " + m_inventory[inputIndex]->getTheName());
        } else if (m_inventory[inputIndex]->isScroll()) {
            // We must use the scroll if the item is a scroll
            Scroll* scrollToUse = (Scroll*)m_inventory[inputIndex];
            scrollToUse->activateScroll();
            getTheTemple()->addAction(scrollToUse->getActionString());
            
            // We must remove the scroll from the inventory and delete it
            m_inventory.erase(m_inventory.begin() + inputIndex);
            delete scrollToUse;
        }
    }
}

void Player::displayMyInventoryW() {
    // We must clear the screen before displaying the inventory
    clearScreen();
    
    // We must print the header for the inventory
    cout << "Inventory:" << endl;

    char letterInd = 'a';
    // We must iterate through the inventory to display each item
    for (int i = 0; i < m_inventory.size(); i++) {
        // We must print each item with its corresponding letter and description
        cout << (char)(letterInd + i) << ". " << m_inventory[i]->getTheName() << endl;
    }
    
    char x = getCharacter();
    int inputIndex = x - letterInd;
    
    // We must check if the input is within the range of inventory slots
    if (inputIndex < m_inventory.size()) {
        if (m_inventory[inputIndex]->isWeapon()) {
            // We must equip the weapon if the item is a weapon
            setTheWeapon((Weapon*)m_inventory[inputIndex]);

            getTheTemple()->addAction("You are wielding " + m_inventory[inputIndex]->getTheName() + ".");
        }
    }
}

void Player::displayMyInventoryS() {
    // We must clear the screen before displaying the inventory
    clearScreen();
    
    // We must print the header for the inventory
    cout << "Inventory:" << endl;

    char letterInd = 'a';
    // We must iterate through the inventory to display each item
    for (int i = 0; i < m_inventory.size(); i++) {
        // We must print each item with its corresponding letter and description
        cout << (char)(letterInd + i) << ". " << m_inventory[i]->getTheName() << endl; // << " - " << m_inventory[i]->getDescription() <<
    }
    
    // should I prompt the player for input to equip a weapon, use a scroll, or exit the inventory - CHECK
    
    char x = getCharacter();
    int inputIndex = x - letterInd;
    
    // We must check if the input is within the range of inventory slots
    if (inputIndex < m_inventory.size()) {
        if (m_inventory[inputIndex]->isScroll()) {
            // We must use the scroll if the item is a scroll
            Scroll* scrollToUse = (Scroll*)m_inventory[inputIndex];
            scrollToUse->activateScroll();
            getTheTemple()->addAction("You read " + m_inventory[inputIndex]->getTheName() + ".");
            getTheTemple()->addAction(scrollToUse->getActionString());
            
            // We must remove the scroll from the inventory and delete it
            m_inventory.erase(m_inventory.begin() + inputIndex);

            delete scrollToUse;
        }
    }
}

void Player::displayMyStats() {
    cout << "Level: " << getTheTemple()->getMyLevel() << ", ";
    cout << "Hit points: " << getTheHP() << ", ";
    cout << "Armor: " << getTheArmor() << ", ";
    cout << "Strength: " << getTheStrength() << ", ";
    cout << "Dexterity: " << getTheDexterity(); // + getWeapon()->getDexBonus();
    cout << endl << endl;
}

    


