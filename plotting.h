#ifndef PLOTTING_H
#define PLOTTING_H

#include <iostream>
#include <string>
#include "players.h"
using namespace std;

// Clear screen function that is compatible with Windows/MacOS/Linux
void clearscreen();

// Dynamically allocate memory for the 2D plot
string ** initPlot (string difficulty, int& plotDimension);

// Calculate the spawn point of the player
// Will be used for the fill plot function
int calcPlayerSpawn(int plotDimension);

// Temporary function to fill hypothetical maze values
// Will be replaced by Anson's work
void loadPlot(string **plot, int plotDimension, int spawnPoint);

// Function to print out the plot which is saved in a 2D array
void printPlot(string **plot, int plotDimension);

// Function to animate a character's movement
void moveAnimation(string **plot, int steps, playerObject& character, string direction, int plotDimension);

#endif
