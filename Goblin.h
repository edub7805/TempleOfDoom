// Goblin.h
// Elijah Willis

#ifndef GOBLIN_INCLUDED
#define GOBLIN_INCLUDED

#include <climits>
#include "Monster.h"
#include "Weapon.h"
#include "utilities.h"


const int GOBLIN_RANGE = 15;

class Goblin: public Monster {
public:
    // Constructor
    Goblin(Temple* temple) : Monster(temple, 'G', "Goblin", randInt(6)+15, 1, 3, 1) {
      setTheWeapon(new ShortSword(temple));
    }
    
    // Destructor
    ~Goblin() {}

    // Action Functions
    void calculateMove() {
        // We must check if the monster is asleep
        if (checkIsAsleep()) { // If the goblin is asleep
            return; // Do nothing and return immediately
        }

        Player* player = getTheTemple()->getMyPlayer(); // Get the player object from the temple
        
        // We must check if the monster is next to the player and attack if true
        if (pathToPlayer() == 1) { // If the goblin is adjacent to the player
            hit(this, (Actor*) player); // Attack the player
        } else { // If the player is not adjacent:
            // Generate char maze for breadth-first search
            char maze[18][70]; // Create a maze representation of the temple
            for (int i = 0; i < 18; i++) { // Loop through rows
                for (int j = 0; j < 70; j++) { // Loop through columns
                    maze[i][j] = ' '; // Initialize each cell to empty space
                }
            }

            vector<vector<int>> path; // We must store route to Player
            vector<int> step; // We must store first step towards Player
            int dist = INT_MAX; // We must store the length of the least-distance path to Player

            // Recursively finds shortest path to Player
            approachPlayer(maze, getTheRowPosition(), getTheColPosition(), player->getTheRowPosition(), player->getTheColPosition(), dist, 0, path, step); // Find the path to the player

            // If step was populated with first step towards Player, move in that direction
            if (step.size() != 0) { // If a step towards the player was found
                move(getTheRowPosition(), getTheColPosition(), step[0], step[1]); // Move the goblin towards the player
            }
        }
    }

    // We must determine if step is valid based on if step is on the border of the dungeon, if step has been visited before, if step isWall, or if step isMonster
    bool isValid(char maze[][NUM_COLS], int sr, int sc) {
        return sr != 0 && sr != NUM_ROWS && sc != 0 && sc != NUM_COLS // Check if the position is within the dungeon boundaries
            && maze[sr][sc] != 'o' // Check if the cell has not been visited
            && !getTheTemple()->isThereWall(sr, sc) // Check if there is no wall at the position
            && !getTheTemple()->isThereMonster(sr, sc); // Check if there is no monster at the position
    }

    void approachPlayer(char maze[][NUM_COLS], int sr, int sc, int er, int ec, int &dist, int newDist, vector<vector<int>> &route, vector<int> &step) {
        // We must return if over Goblin's smell range or longer route than the shortest path thus far
        if (newDist > GOBLIN_RANGE || newDist > dist) { // If the current path length exceeds the goblin's smell range or the shortest path found so far
            return; // Do nothing and return
        }

        // If reached Player...
        if (sr == er && sc == ec) { // If the current position is the player's position
            if (newDist < dist) { // If the new path is shorter than the previous shortest path
                dist = newDist; // Update the shortest path length
                step = route[1]; // Update the first step towards the player
            }
            return; // Return after updating the shortest path
        }
        
        // We must mark the current cell as visited
        maze[sr][sc] = 'o'; // Mark the current cell as visited
        route.push_back({sr, sc}); // Add the current cell to the route

        // We must recursively traverse in each direction
        if (isValid(maze, sr + 1, sc)) { // If moving down is valid
            approachPlayer(maze, sr + 1, sc, er, ec, dist, newDist + 1, route, step); // Move down and continue searching
        }

        if (isValid(maze, sr - 1, sc)) { // If moving up is valid
            approachPlayer(maze, sr - 1, sc, er, ec, dist, newDist + 1, route, step); // Move up and continue searching
        }

        if (isValid(maze, sr, sc + 1)) { // If moving right is valid
            approachPlayer(maze, sr, sc + 1, er, ec, dist, newDist + 1, route, step); // Move right and continue searching
        }

        if (isValid(maze, sr, sc - 1)) { // If moving left is valid
            approachPlayer(maze, sr, sc - 1, er, ec, dist, newDist + 1, route, step); // Move left and continue searching
        }

        // We must back-track from the current cell if it is not part of the solution path
        maze[sr][sc] = ' '; // Mark the cell as unvisited (backtracking)
        route.pop_back(); // Remove the current cell from the route
    }

    // We must randomly drop a GameObject
    GameObject* dropAGameObject() {
      if (!isOverGameObject() && trueWithProbability(1/3)) {
        Weapon* dropped = trueWithProbability(1/2) ? (Weapon*)(new MagicAxe(getTheTemple())) : (Weapon*)(new MagicFangs(getTheTemple()));
        return dropped;
      }
      return nullptr;
    }

};

#endif // GOBLIN_INCLUDED
