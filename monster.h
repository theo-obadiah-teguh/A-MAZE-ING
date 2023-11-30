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

void monsterNo(string difficulty, int & monsterCount);

void createMonsters(int monsterCount);

void monsterDir(playerObject player);

void init(int rowSize, int columnSize, string ** myPlot, int monsterCount);

void monsterSteps(string ** myPlot, int rowSize, int columnSize);

bool checkValid(int monsterCount, int & monsterSteps, string ** myPlot, int rowSize, int columnSize);

void huntMonster(string ** array, int & monsterCount);

#endif
