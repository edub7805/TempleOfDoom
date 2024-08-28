// Temple.h
// Elijah Willis

#ifndef TEMPLE_INCLUDED
#define TEMPLE_INCLUDED

#include <stdio.h>
#include <vector>
#include <queue>
#include <string>
#include "utilities.h"

using namespace std;

// Forward declarations to avoid circular dependencies and create pointers to objects of the following classes
class allObjects;
class GameObject;
class Space;
class Wall;
class Actor;
class Player;
class Monster;
class Weapon;

// This is the Class to represent our temple, including other classes
class Temple {
    
public:
    
  // My Constructor
  Temple();
    
  // My Destructor
  ~Temple();
    
    // These are my boolean accessor functions
    bool isTheGameOver();
    bool isThereSpace(int rowPosi, int colPosi);
    bool isThereWall(int rowPosi, int colPosi);
    bool isThereMonster(int rowPosi, int colPosi);
    bool isThereActor(int rowPosi, int colPosi);
    bool isTherePlayer(int rowPosi, int colPosi);
    bool isThereGameObject(int rowPosi, int colPosi);
    bool areMonstersRemaining();
    
  
    // These are my Accessor functions
    int     getMyLevel();
    Player* getMyPlayer();
    allObjects* getMyObject(int rowPos, int colPos);
    

      
    // Functions to move to the next level and update the level
  void nextLevel();
  void setTheObjectPosition(allObjects* object);
  void generateTheRandomPosition(allObjects* object, int &pR, int &pC);
  void updateTheCurrentCell(Actor* a, int cr, int cc);
  void updateTheNextCell(Actor* a, int nr, int nc);

  
  // Functions to display my Level Actions
  void displayActions();
  void displayLevel();
  void addAction(string action);


  
  // Monsters
  void destroyTheMonster(Monster* monster); // pointer to a monster to delete it from memory
  void monsterMovement();

  
  // Result of Action
  void pickUpGameTheObject(GameObject* gameObject); // picking up the game object
  
  // Result of the game
  void endTheGame(string des);
  
private:
  bool          is_thegameOver;
  int           m_level;
    allObjects*       m_maze[NUM_ROWS][NUM_COLS]; // we still need to implement the object class
  queue<string> m_action;
  
  Player*             m_player;
  Space*              m_spaces[NUM_ROWS][NUM_COLS];
  Wall*               m_walls[NUM_ROWS][NUM_COLS];
  vector<Monster*>    m_monsters;
  vector<GameObject*> m_gameObjects;
  
  // Functions that create my level with all its correcg attributes
  void createTheSpaces();
  void createTheGameObjects();
  void createTheWalls();
  void createThePlayer();
  void createTheMonsters();
  void createTheRooms(vector<vector<int>> &rooms);
  void isCorridorType(int &corridorType, vector<vector<int>> rooms, int x, int y, int a, int b, int c, int m, int n);
  void createTheCorridors(int curRow, int curCol, bool changeCol, int delta);

  
  // Functions to reset my level
  void resetLevel();
  void resetCell(allObjects* object); // pointer to an object
  
  // Random functions acting as helpers
  GameObject* createARandomGameObject();
  Monster*    createARandomMonster();
};

#endif /* Temple_h */
 
