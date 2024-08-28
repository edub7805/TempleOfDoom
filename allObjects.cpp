// allObjects.cpp
// Elijah Willis

#include "allObjects.h"

// Here are my 2 different constructors for allObjects
allObjects::allObjects(Temple* temple, char symbol, string name, int rowPos, int colPos) : m_temple(temple), m_symbol(symbol), m_name(name), m_pos_row(rowPos), m_pos_col(colPos) {}

allObjects::allObjects(Temple* temple, char symbol, string name) : m_temple(temple), m_symbol(symbol), m_name(name), m_pos_row(-1), m_pos_col(-1) {}


// Boolean accessors
bool allObjects::isActor() {
  return (isMonster() or isPlayer());
}

bool allObjects::isPlayer() {
  return (m_symbol == '@');
}

bool allObjects::isMonster() {
  return (m_symbol == 'B' or m_symbol == 'D' or m_symbol == 'G' or m_symbol == 'S');
}

void allObjects::setTheSymbol() {
    m_symbol = ' ';
}


bool allObjects::isGameObject() {
  return (m_symbol == '?' or m_symbol == ')' or m_symbol == '&' or m_symbol == '>');
}

bool allObjects::isSpace() {
  return (m_symbol == ' ');
}

bool allObjects::isWall() {
  return (m_symbol == '#');
}

// Other types of accessors
Temple* allObjects::getTheTemple() {
  return m_temple;
}

int allObjects::getTheRowPosition() {
  return m_pos_row;
}

int allObjects::getTheColPosition() {
  return m_pos_col;
}

char allObjects::getTheSymbol() {
  return m_symbol;
}

string allObjects::getTheName() {
  return m_name;
}

vector<int> allObjects::getPosition() {
    vector<int> output;
    output[0]=m_pos_row;
    output[1]=m_pos_col;
    return(output);
}

void allObjects::deleteObj() {
    m_symbol = ' ';
  }


// The mutator for changing the position
void allObjects::setPosition(int pR, int cR) {
  m_pos_row = pR;
  m_pos_col = cR;
}
