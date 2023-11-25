#ifndef PLOTTING_H
#define PLOTTING_H

#include <iostream>
#include <string>
#include "players.h"
#include "shop.h"
using namespace std;

// Clear screen function that is compatible with Windows/MacOS/Linux
void clearscreen ();

// File I/O Functions for loading and deleting dynamic 2D arrays
// Reads the dimensions of a text input
void readTextDimensions (int & rowSize, int & columnSize, string filename);

// Reads the characters of a text input and stores them to an array
void readTextToArray (string **& array, int rowLength, int columnLength, string filename, string type);

// Initializes a 2D plot with readTextDimensions and readTextToArray, returns a pointer to the plot
string ** initPlot (string filename, string type, int & rowSize, int & columnSize, string difficulty = "");

// Deletes a given 2D array
void deleteArray (string **& array, int rowSize);

// Selecting different maps based on the chosen difficulty level
string selectPlot (string difficulty);

// Randomizes the required exit for the win condition
string randomExit ();

// Prints a given 2D plot
void printPlot (string ** array, int rowSize, int columnSize, string exitPoint, bool fixPosition = false);

// Calculates the player's spawning point
void calcPlayerSpawn (int & rowSize, int & columnSize);

// Function to animate a character's movement
void moveAnimation (string **plot, int steps, playerObject& character, string direction, int rowSize, int columnSize, int oins, int timeLimit, bool & win, string exitPoint);

#endif
