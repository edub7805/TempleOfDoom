// Game.cpp
// Elijah Willis

#include "Game.h"
#include "Temple.h"
#include "utilities.h"
#include "Player.h"
#include <iostream>
using namespace std;

// Implement these and other Game member functions you may have added.

Game::Game(int goblinSmellDistance) {
    m_temple = new Temple();
}

Game::~Game() {
    delete m_temple;
}

void Game::play()
{
    char input;
    

      while (true) {
    
       // this will help output the game onto terminal
        m_temple->displayLevel();
        m_temple->getMyPlayer()->displayMyStats();
        m_temple->displayActions();
        
        // Quit game if game over
          if (m_temple->isTheGameOver()) {
                exit(-1);
              }

          // Get keyboard command
          input = getCharacter();
          cout << endl << endl;
        
        // Bool to determine if monsters should move
        bool didPlayerMove = false;
        
        switch(input) {
          case ARROW_LEFT:
          case ARROW_RIGHT:
          case ARROW_UP:
          case ARROW_DOWN:
                // Attempt to move player in direction
                clearScreen();
                m_temple->getMyPlayer()->calculateAMove(input);
                didPlayerMove = true;
                break;
          case 'g':
                // Attempt to pick up object
                clearScreen();
                didPlayerMove = m_temple->getMyPlayer()->commitAnAction();
                break;
            case '>':
                // Attempt to descend stairs
                clearScreen();
                didPlayerMove = m_temple->getMyPlayer()->commitAnActionStair();
                break;
          case 'i':
                // Display inventory
                clearScreen();
                m_temple->getMyPlayer()->displayMyInventory();
                didPlayerMove = m_temple->getMyPlayer()->commitAnAction();
                break;
            case 'w':
                // Display inventory
                clearScreen();
                m_temple->getMyPlayer()->displayMyInventoryW();
                didPlayerMove = m_temple->getMyPlayer()->commitAnAction();
                break;
            case 'r':
                // Display inventory
                clearScreen();
                m_temple->getMyPlayer()->displayMyInventoryS();
                didPlayerMove = m_temple->getMyPlayer()->commitAnAction();
                break;
          case 'q':
                m_temple->getMyPlayer()->adjustTheHP(-50);
                m_temple->endTheGame("");
                break;
          case 'c':
                clearScreen();
                
                // Cheat mode by maxing all stats
                m_temple->getMyPlayer()->cheatMode();
                didPlayerMove = m_temple->getMyPlayer()->commitAnAction();
                break;
        }
        
        // If player made a move, move monsters
        if (didPlayerMove) {
          m_temple->monsterMovement();
        }
      }
    }
