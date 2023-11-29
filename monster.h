#ifndef GHOST_H
#define GHOST_H
#include <string>
#include <vector>
using namespace std;
#include "players.h"

struct monsterObject{
    int direction;
    int vertical_ax;
    int horizontal_ax;
};
//add extern to try avoid duplicate error
extern vector<monsterObject *> monster;

void monsterNo(string difficulty, int &monsterCount);
void createMonsters(int monsterCount);
void monsterDir(playerObject player);
void init(int rowSize, int columnSize, string ** myPlot, int monsterCount);
void monsterSteps(string ** myPlot, int rowSize, int columnSize);
bool checkValid(int monsterCount, int &monsterSteps, string ** myPlot, int rowSize, int columnSize);
//update hunt_monster function and updated in shop.cpp
void huntMonster(string ** array);
#endif
