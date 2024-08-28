// allObjects.h
// Elijah Willis

#ifndef ALLOBJECTS_INCLUDED
#define ALLOBJECTS_INCLUDED

#include <iostream>
#include <string>
#include "Temple.h"

using namespace std;

// This is the Parent class for all game objects and player. It contains all objects and detail out their positions, etc
class allObjects {
    
public:

    // Constructors of different types
    allObjects(Temple* temple, char symbol, string name);
    allObjects(Temple* temple, char symbol, string name, int rowPos, int colPos);
    virtual ~allObjects() {};
  
    // My boolean accessors
    bool isActor();
    bool isPlayer();
    bool isGameObject();
    bool isSpace();
    bool isWall();
    bool isMonster();

    // Accessors of different types
    Temple* getTheTemple();
    char     getTheSymbol();
    string   getTheName();
    int      getTheRowPosition();
    int      getTheColPosition();
    void setTheSymbol();
    void deleteObj();
  
    // Changing the position (single mutator)
    void setPosition(int pR, int cR);
    vector<int> getPosition();
  
private:
    int      m_pos_row;
    Temple*  m_temple;
    string   m_name;
    int      m_pos_col;
    char     m_symbol;
};

// Wall ('#') Class
class Wall : public allObjects {

public:
    Wall(Temple* temple, int rowPos, int colPos) : allObjects(temple, '#', "Wall", rowPos, colPos) {}
};

// Space (' ') Class
class Space : public allObjects {
    
public:
    
    Space(Temple* temple, int rowPos, int colPos) : allObjects(temple, ' ', "Space", rowPos, colPos) {}
};

#endif // ALLOBJECTS_INCLUDED

