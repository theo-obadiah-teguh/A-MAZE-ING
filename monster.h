#ifndef GHOST_H
#define GHOST_H
#include <string>
#include <vector>
#include "players.h"
using namespace std;

struct monsterObject{
    int direction;
    int vertical_ax;
    int horizontal_ax;
};

// Avoid duplicate error
extern vector<monsterObject *> monster;

// Calculates the number of monsters to generate
void monsterNo(string difficulty, int & monsterCount);

// Creates a vector of "empty" monsters
void createMonsters(int monsterCount);

// Pops all the monsters in the vector
void deleteMonsters(int monsterCount);

// Determine the monsters' direction of movement
void monsterDir(playerObject player);

// Spawns the monsters randomly throughout the maze
void init(int rowSize, int columnSize, string ** myPlot, int monsterCount);

// Randomly determines the number of the steps the monsters will take
void monsterSteps(string ** myPlot, int rowSize, int columnSize);

// Conditions to check the validity of monsters' movements
bool checkValid(int monsterCount, int & monsterSteps, string ** myPlot, int rowSize, int columnSize);

// Function implemented in shop.cpp to kill a singular monster
void huntMonster(string ** array, int & monsterCount);

#endif
