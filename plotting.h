#ifndef PLOTTING_H
#define PLOTTING_H
using namespace std;

const int plotHeight = 31;
const int plotWidth = 31;

string Plot [plotHeight][plotWidth];
const int spawnPoint = 15; // Middle of the plot is the starting point

// Temporary function to generate hypothetical maze
// Will be replaces by Anson's work
void createPlot();

// Function to print out the plot which is saved in a 2D array
void printPlot();

#endif
