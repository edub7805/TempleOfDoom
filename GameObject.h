// GameObject.h
// Elijah Willis

#ifndef GAMEOBJECT_INCLUDED
#define GAMEOBJECT_INCLUDED

#include "allObjects.h"

class GameObject: public allObjects {
    
public: 
    // Constructing monsters
    GameObject(Temple* temple, char symbol, string name) : allObjects(temple, symbol, name) {}
    
    //Constructing weapons and scrolls
    GameObject(Temple* temple, char symbol, string name, string description, string actionString) : allObjects(temple, symbol, name), m_characterization(description), m_actionString(actionString) {}

    // Virtual Destructor for derived classes
    virtual ~GameObject() {}
    
    // Here are my boolean accessors for my GameObjects, which function the exact same way as those for the allobjects class
    
    bool isScroll() {
      return getTheSymbol() == '?';
    }
    
    bool isStairs() {
      return getTheSymbol() == '>';
    }

    bool isWeapon() {
      return getTheSymbol() == ')';
    }
    
    bool isGoldenIdol() {
      return getTheSymbol() == '&';
    }
    
    // Here are my other accessors, which function the exact same way as those for the allobjects class
    string getDescription() {
      return m_characterization;
    }
    
    string getActionString() {
      return m_actionString;
    }
    
  private:
    string m_characterization;
    string m_actionString;
};


#endif // GAMEOBJECT_INCLUDED
