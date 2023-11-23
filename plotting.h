#ifndef PLOTTING_H
#define PLOTTING_H

#include <iostream>
#include <string>
#include "players.h"
#include "shop.h"
using namespace std;

// Clear screen function that is compatible with Windows/MacOS/Linux
void clearscreen();

// Dynamically allocate memory for the 2D plot
string SelectPlot (string difficulty);

string ** initPlot(string difficulty, int &plotDimension);

// Calculate the spawn point of the player
// Will be used for the fill plot function
int calcPlayerSpawn(int &row_size, int &column_size);

void loadPlot(string ** plot, int plotDimension, int spawnPoint);

// Function to animate a character's movement
void moveAnimation(string **plot, int steps, playerObject& character, string direction, int row_size, int column_size, int coin, int time);

#endif
