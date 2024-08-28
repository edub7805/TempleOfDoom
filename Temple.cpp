// Temple.cpp
// Elijah Willis

#include <iostream>
#include <set>

#include "Temple.h"
#include "Player.h"
#include "allObjects.h"
#include "Bogeyman.h"
#include "Snakewoman.h"
#include "Dragon.h"
#include "Goblin.h"
#include "Weapon.h"
#include "Scroll.h"
#include "utilities.h"

using namespace std;


// Constructor for the Temple
Temple::Temple() : m_level(0), is_thegameOver(false), m_player(nullptr) {
    // Giving each level its attributes, they must be created in the following order.
    createTheWalls();
    createTheSpaces();
    createTheMonsters();
    createTheGameObjects();
    createThePlayer();
}

// Destructor for the Temple
Temple::~Temple() {
    // We must reset the level, and then delete the player
    resetLevel();
    delete m_player;
}

// My boolean Accessor functions

bool Temple::isTheGameOver() {
    return is_thegameOver;
}

bool Temple::isThereSpace(int rowPosi, int colPosi) {
    // Checking if there's space
    return m_maze[rowPosi][colPosi]->isSpace();
}

bool Temple::isThereWall(int rowPosi, int colPosi) {
    // Checking if there's a wall
    return m_maze[rowPosi][colPosi]->isWall();
}
bool Temple::isThereMonster(int rowPosi, int colPosi) {
    // Checking if there's a monster
    return m_maze[rowPosi][colPosi]->isMonster();
}
bool Temple::isThereActor(int rowPosi, int colPosi){
    // Checking if there's an actor
    return m_maze[rowPosi][colPosi]->isActor();
}
bool Temple::isTherePlayer(int rowPosi, int colPosi) {
    // Checking if there's a player
    return m_maze[rowPosi][colPosi]->isPlayer();
}
bool Temple::isThereGameObject(int rowPosi, int colPosi) {
    // Checking if there's any type of object
    
    return m_maze[rowPosi][colPosi]->isGameObject();
}
bool Temple::areMonstersRemaining() {
    // See how manh monsters remain
    return m_monsters.size() > 0;
}


// Here are my normal accessor functions

int Temple::getMyLevel() {
  return m_level;
}

Player* Temple::getMyPlayer() {
  return m_player;
}

allObjects* Temple::getMyObject(int rowPosi, int colPosi) {
  return m_maze[rowPosi][colPosi];
}

// Here are my functions to create the rooms

void Temple::createTheWalls() {
    // Create a wall for every space in the level
 for (int i = 0; i < NUM_ROWS; i++) {
    for (int j = 0; j < NUM_COLS; j++) {
        Wall* nWall = new Wall(this, i, j);  // Create a new wall at the current position
        m_walls[i][j] = nWall;  // Store the wall in the walls array
        m_maze[i][j] = nWall;  // Also store the wall in the maze array (if maze is used for navigation)
     }
   }
}


void Temple::createTheSpaces() {
    // all spaces must be nullptr
    for (int i = 0; i < NUM_ROWS; i++) {
       for (int j = 0; j < NUM_COLS; j++) {
         m_spaces[i][j] = nullptr;
       }
     }

vector<vector<int>> rooms; // We store the coordinates of rooms as {startRow, startCol, endRow-1, endCol-1}

// We build non-overlapping rooms
createTheRooms(rooms);

    vector<vector<int>> corridorTypes(rooms.size(), vector<int>(rooms.size(), -1)); // We store the direction of corridors between rooms

// We initialize values for distances and corridorTypes
for (int f = 0; f < rooms.size(); f++) {
    for (int g = 0; g < rooms.size(); g++) {
        corridorTypes[f][g] = -1; // We initialize all corridor types to -1 (no corridor)
    }
}

// We loop through every combination of rooms in both directions
for (int f = 0; f < rooms.size(); f++) {
    for (int g = 0; g < rooms.size(); g++) {
        // If room is the same or corridor has already been made, we continue
        if (f == g or corridorTypes[f][g] == -2) {
            continue; // We skip if it's the same room or corridor already exists
        }
        
        int corridorType = -1;
        
        // We determine if a corridor is possible from room f to g
        isCorridorType(corridorType, rooms, f, g, 0, 0, 1, 7, 2);
        isCorridorType(corridorType, rooms, f, g, 2, 0, 1, 6, 3);
        isCorridorType(corridorType, rooms, f, g, 1, 1, 0, 0, 5);
        isCorridorType(corridorType, rooms, f, g, 3, 1, 0, 1, 4);
        
        // We check if a corridor is possible...
        if (corridorType > 0) {
            // We avoid creating a corridor to the same room
            corridorTypes[g][f] = -2; // We mark the reverse direction as blocked
            
            // We create a corridor between f and g
            switch (corridorType) {
                case 0:
                    // We create a corridor from the top-left corner going up
                    createTheCorridors(rooms[f][0], rooms[f][1], false, -1);
                    break;
                case 1:
                    // We create a corridor from the top-right corner going up
                    createTheCorridors(rooms[f][0], rooms[f][3], false, -1);
                    break;
                case 2:
                    // We create a corridor from the top-right corner going right
                    createTheCorridors(rooms[f][0], rooms[f][3], true, 1);
                    break;
                case 3:
                    // We create a corridor from the bottom-right corner going right
                    createTheCorridors(rooms[f][2], rooms[f][3], true, 1);
                    break;
                case 4:
                    // We create a corridor from the bottom-right corner going down
                    createTheCorridors(rooms[f][2], rooms[f][3], false, 1);
                    break;
                case 5:
                    // We create a corridor from the bottom-left corner going down
                    createTheCorridors(rooms[f][2], rooms[f][1], false, 1);
                    break;
                case 6:
                    // We create a corridor from the bottom-left corner going left
                    createTheCorridors(rooms[f][2], rooms[f][1], true, -1);
                    break;
                case 7:
                    // We create a corridor from the top-left corner going left
                    createTheCorridors(rooms[f][0], rooms[f][1], true, -1);
                    break;
                }
            }
        }
    }
}

void Temple::createTheRooms(vector<vector<int>> &rooms) {
    int totalArea = 0;
    int attempts = 0;
    
    // Loop until total area reaches the desired area or maximum attempts reached
    while (totalArea < 300 && attempts < 10000) {
        attempts++; // Increase number of attempts
        
        // Generate random starting coordinates for the room
        int startRow = randInt(NUM_ROWS - 2 - 5) + 1;
        int startCol = randInt(NUM_COLS - 2 - 7) + 1;
        
        // Generate random dimensions for the room within certain limits
        int endRow = startRow + randInt(6) + 5;
        int endCol = startCol + randInt(10) + 7;
        
        // Check if room extends beyond the temple boundaries
        if (endRow > 17 || endCol > 69) {
            continue; // Skip current iteration if room is invalid
        }
        
        // Check if the room overlaps with existing spaces
        for (int i = 0; i < 18; i++) {
            for (int j = 0; j < 70; j++) {
                if (m_spaces[i][j] != nullptr && i >= startRow - 1 && i <= endRow + 1 &&
                    j >= startCol - 1 && j <= endCol + 1) {
                    goto cont; // Skip to next iteration if overlap found
                }
            }
        }

        // Create the room
        rooms.push_back({startRow, startCol, endRow - 1, endCol - 1});
        for (int i = startRow; i < endRow; i++) {
            for (int j = startCol; j < endCol; j++) {
                Space* newSpace = new Space(this, i, j); // Deleted in resetLevel
                m_spaces[i][j] = newSpace;
                m_maze[i][j] = newSpace;
            }
        }
        
        // Calculate and accumulate the area of the created room
        totalArea += (endRow - startRow) * (endCol - startCol);
        
        // Continue to the next iteration
        cont:;
    }
}
void Temple::isCorridorType(int &corridorType, vector<vector<int>> rooms, int x, int y, int a, int b, int c, int m, int n) {
  if (rooms[x][a] >= rooms[y][b] and rooms[x][a] <= rooms[y][b+2]) {
    if (rooms[x][c] > rooms[y][c]) {
      corridorType = m;
    } else {
      corridorType = n;
    }
  }
}

void Temple::createTheCorridors(int curRow, int curCol, bool changeCol, int delta) {
  // We must start by offsetting the corner of the room by one
  if (changeCol) {
    curCol += delta;
  } else {
    curRow += delta;
  }
  
  // We must continue creating corridors while the cell is a wall and is not on the edge of the level
  while (isThereWall(curRow, curCol) and curRow > 0 and curRow < NUM_ROWS and curCol > 0 and curCol < NUM_COLS) {
    // We must create a new space at the current cell
    Space* newSpace = new Space(this, curRow, curCol); // deleted in resetLevel
    m_spaces[curRow][curCol] = newSpace;
    m_maze[curRow][curCol] = newSpace;
    
    // We must update the cell in the correct direction
    if (changeCol) {
      curCol += delta;
    } else {
      curRow += delta;
    }
  }
}

void Temple::createThePlayer() {
    // We must create a new Player object and set its position
    m_player = new Player(this);
    setTheObjectPosition(m_player);
}

void Temple::createTheMonsters() {
    // We must determine the number of monsters to generate based on the current level
    int numMonsters = randInt(2, 5 * (m_level + 1) + 1);
    
    if(m_level >= 2 && m_level <= 4) {
        Monster* addMonster = createARandomMonster();
        m_monsters.push_back(addMonster);
        setTheObjectPosition(addMonster);
    }
    // We must iterate to create and add monsters to the level
    for (int i = 0; i <= numMonsters; i++) {
        // We must generate a random monster and add it to the level
        Monster* addMonster = createARandomMonster();
        m_monsters.push_back(addMonster);
        setTheObjectPosition(addMonster);
    }
}

void Temple::createTheGameObjects() {
    // We must generate random GameObjects for the level
    // We must create stairs to the next level if not on the last level
    if (m_level >=0 && m_level < 4) {
        GameObject* stairs = new GameObject(this, '>', "Stairs"); // deleted in resetLevel
        m_gameObjects.push_back(stairs);
        setTheObjectPosition(stairs);
    }
    
    int numGameObjects = randInt(1) + 2;
 
    // We must iterate to create and add game objects to the level
    for (int i = 0; i < numGameObjects; i++) {
        // We must generate a random game object and add it to the level
        GameObject* addGameObject = createARandomGameObject();
        m_gameObjects.push_back(addGameObject);
        setTheObjectPosition(addGameObject);
    }
        // We must create a golden idol if on the last level
    if (m_level == 4) {
        GameObject* goldenIdol = new GameObject(this, '&', "Golden Idol"); // deleted in resetLevel
        m_gameObjects.push_back(goldenIdol);
        setTheObjectPosition(goldenIdol);
    }
}

// Object position setter
void Temple::setTheObjectPosition(allObjects* object) {
     // creating new coordinates
    int pR = -1;
    int cR = -1;
    // We must generate random position and set Object's position accordingly
    generateTheRandomPosition(object, pR, cR);
    object->setPosition(pR, cR);
    // If Object is GameObject and there is already an Actor on the space...
    if (object->isGameObject() && isThereActor(pR, cR)) {
      // Set Actor's overGameObject to GameObject
        Actor* actor = (Actor*)getMyObject(pR, cR);
      actor->setOverAGameObject((GameObject*)object);
    } else {
      // Set maze's position to object
      m_maze[pR][cR] = object;
    }
}

// Monster/player generating functions

Monster* Temple::createARandomMonster() {
    // Randomly selects the number of choices based on the current level
    int x;
    if (m_level >= 3) {
        x = 4; // Higher level unlocks more choices
    } else {
        x = 3; // Only three choices available for lower levels
    }
    
    // Randomly selects a monster based on the number of choices
    int random = randInt(x);
    if (random == 0) {
        if(m_level >=2 && m_level <= 4) {
            return new Bogeyman(this);
        } // Returns a Bogeyman
    } else if (random == 1) {
        return new Snakewoman(this); // Returns a Snakewoman
    } else if (random == 2) {
        return new Goblin(this); // Returns a Goblin
    } else if (random == 3) {
        if(m_level >=3 && m_level <= 4) {
            return new Dragon(this);
        }  // Returns a Dragon
    }
    return new Snakewoman(this); // Default: Returns a Bogeyman
}

GameObject* Temple::createARandomGameObject() {
    // Randomly selects a game object
    int random = randInt(7);
    if (random == 0) {
        return new Mace(this); // Returns a Mace
    } else if (random == 1) {
        return new ShortSword(this); // Returns a ShortSword
    } else if (random == 2) {
        return new LongSword(this); // Returns a LongSword
    } else if (random == 3) {
        return new HealthScroll(this); // Returns a HealthScroll
    } else if (random == 4) {
        return new ArmorScroll(this); // Returns an ArmorScroll
    } else if (random == 5) {
        return new StrengthScroll(this); // Returns a StrengthScroll
    } else {
        return new DexterityScroll(this); // Returns a DexterityScroll
    }
    return new ShortSword(this); // Default: Returns a ShortSword
}

void Temple::generateTheRandomPosition(allObjects* object, int &pR, int &pC) {
    // We must continue generating random positions until a valid one is found
    while(true) {
        // Generate random row and column positions
        pR = randInt(NUM_ROWS);
        pC = randInt(NUM_COLS);
        // If we can place the object inside a cell, meaning there is no impenetrable wall
        if (!isThereWall(pR, pC) && (
                                     (object->isActor() && !isThereActor(pR, pC)) ||
                                     (object->isGameObject() && !isThereGameObject(pR, pC)))) {
                                         return;
                                     }
    }

}

// Next/reset level functions

void Temple::nextLevel() {
    // I reset the level to prepare for the next stage.
    resetLevel();
    // Then, I advance to the next level.
    m_level++;
    // I create the walls to define the boundaries of the new level.
    createTheWalls();
    // I allocate spaces within the level for movement and interaction.
    createTheSpaces();
    // I populate the new level with monsters to challenge the player.
    createTheMonsters();
    // I scatter game objects across the level to provide items and challenges.
    createTheGameObjects();
    // I position the player within the new level.
    setTheObjectPosition(m_player);
}

void Temple::resetLevel() {
    // I clear the level of all monsters.
    while (!m_monsters.empty()) {
        allObjects* t = m_monsters.back();
        m_monsters.pop_back();
        delete t;
    }
    
    // I remove all game objects, including weapons, scrolls, stairs, and the golden idol.
    while (!m_gameObjects.empty()) {
        allObjects* t = m_gameObjects.back();
        m_gameObjects.pop_back();
        delete t;
    }
    
    // I erase all spaces and walls from the level.
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            delete m_spaces[i][j];
            m_spaces[i][j] = nullptr;
            
            delete m_walls[i][j];
            m_walls[i][j] = nullptr;
        }
    }
}

// Functions that update movement

void Temple::updateTheCurrentCell(Actor* a, int cr, int cc) {
  if (a->isOverGameObject()) {
    m_maze[cr][cc] = a->getOverTheGameObject(); 
  } else {
      m_maze[cr][cc] = m_spaces[cr][cc];
  }
}

void Temple::updateTheNextCell(Actor* a, int nr, int nc) {
  m_maze[nr][nc] = a;
}

void Temple::displayLevel() {
    // I clear the screen to prepare for displaying the current level.
    clearScreen();
    
    // I use a while loop to iterate through the maze and display the symbols of each object.
    int i = 0;
    while (i < 18) {
        int j = 0;
        while (j < 70) {
            cout << m_maze[i][j]->getTheSymbol();
            j++;
        }
        cout << endl;
        i++;
    }
    cout << endl;
}

// I display the game actions that have occurred.
void Temple::displayActions() {
    // While there are actions in the queue, I display each one.
    while(!m_action.empty()) {
        cout << m_action.front() << endl;
        m_action.pop();
    }
    
    cout << endl;
}

// adding a game action to the queue if the game is not over.
void Temple::addAction(string action) {
    // adding a game action to the queue if the game is not over.
    !is_thegameOver ? m_action.push(action) : void();
}


// All monsters must execute their moves
void Temple::monsterMovement(){
int i = 0;
while (i < m_monsters.size()) {
    m_monsters[i]->calculateMove();
    
    // Check if the game has ended
    if (is_thegameOver) {
        return;
    }
    i++;
}
}

// Eliminates a defeated monster
void Temple::destroyTheMonster(Monster* monster) {
    // Add a message indicating the monster's defeat
    addAction(monster->getTheName() + " has been vanquished!");
    
    // Iterate through all monsters
    int index = 0;
    while (index < m_monsters.size()) {
        // When the monster is located...
        if (m_monsters[index] == monster) {
            int row = monster->getTheRowPosition();
            int col = monster->getTheColPosition();
            
            // Check if the monster drops an item
            GameObject* droppedItem = monster->dropAGameObject();
            if (droppedItem != nullptr) {
                // Place the dropped item in the current cell
                m_gameObjects.push_back(droppedItem);
                m_maze[row][col] = droppedItem;
                droppedItem->setPosition(row, col);
            } else {
                // Update the current cell with either an existing game object or an empty space
                updateTheCurrentCell(monster, row, col);
            }
            
            // Remove the monster from the vector and deallocate memory
            m_monsters.erase(m_monsters.begin() + index);
            delete monster;
        }
        index++;
    }
}

void Temple::pickUpGameTheObject(GameObject* gameObject) {
    // player can pick up the specified game object
    int index = 0;
    while (index < m_gameObjects.size()) {
        if (m_gameObjects[index] == gameObject) {
            m_gameObjects.erase(m_gameObjects.begin() + index);
        }
        index++;
    }

}

// Win/Lose function

void Temple::endTheGame(string des) {
  addAction(des);
  is_thegameOver = true;
}

