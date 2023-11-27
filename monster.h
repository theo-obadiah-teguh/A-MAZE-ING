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
//updated monster_count
/*
int monster_count;
if (difficulty == "easy") {
  monster_count = 3;
}
else if (difficulty == "medium") {
  monster_count = 5;
}
else if (difficulty == "hard") {
  monster_count = 7;
}
 */
/*
vector<monsterObject *> monster;
for (int i = 0; i < monster_count; i++){
    monster.push_back(new monsterObject);
}*/
//void -> int
int monster_no(string difficulty, int &monster_count);
void create_monsters(int monster_count);
void monster_dir(playerObject player);
void init(int rowSize, int columnSize, string ** myPlot, int monster_count);
void monster_steps(string ** myPlot, int rowSize, int columnSize);
bool check_valid(int monster_count, int &monster_steps, string ** myPlot, int rowSize, int columnSize);
//update hunt_monster function and updated in shop.cpp
void hunt_monster();
#endif
