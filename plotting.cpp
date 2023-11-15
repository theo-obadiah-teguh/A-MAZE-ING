#include "players.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

// Clear screen function that we will use
void clearscreen() {
    system("cls||clear");
}

// Dynamically create 2D arrays for the plots based on the desired difficulty level
string ** initPlot (string difficulty, int& plotDimension) {
  if (difficulty == "easy") {
    plotDimension = 31;
    string **plot = new string*[plotDimension];
    for (int i = 0; i < plotDimension; i++) {
      plot[i] = new string[plotDimension];
    }
    return plot;
  }
  else if (difficulty == "medium") {
    plotDimension = 41;
    string **plot = new string*[plotDimension];
    for (int i = 0; i < plotDimension; i++) {
      plot[i] = new string[plotDimension];
    }
    return plot;
  }
  else if (difficulty == "hard") {
    plotDimension = 51;
    string **plot = new string*[plotDimension];
    for (int i = 0; i < plotDimension; i++) {
      plot[i] = new string[plotDimension];
    }
    return plot;
  }
  else {
    sleep(1);
    clearscreen();
    cout << "Invalid Difficulty!" << endl;
    return NULL;
  }
}

// Calculate the spawn point of the player, which is the middle of the map
int calcPlayerSpawn(int plotDimension) {
  int result = (plotDimension - 1) / 2;
  return result;
}

// Load in the characters that form the maze, from the .txt file to the array
void loadPlot(string **plot, int plotDimension, int spawnPoint) {
  for(int i = 0; i < plotDimension; i++) {
    for(int j = 0; j < plotDimension; j++) {
      if (i == spawnPoint && j == spawnPoint) {
        plot[i][j] = "O";
      }
      else {
        plot[i][j] = "*";
      }
    }
  }
}

void printPlot(string **plot, int plotDimension) {
  string result = "";

  for(int i = 0; i < plotDimension; i++) {
    string line = "";
    for(int j = 0; j < plotDimension; j++) {
      line += plot[i][j];
    }
    result = result + line + '\n';
    }
    cout << result;
}

void moveAnimation(string **plot, int steps, playerObject& character, string direction, int plotDimension) { // Use & to actually edit the struct
  clearscreen();
  for(int i = 0; i < steps; i++) {
    plot[character.vertical][character.horizontal] = '*';

    if (direction == "up")
      character.vertical--;
    else if (direction == "down")
      character.vertical++;
    else if (direction == "right")
      character.horizontal++;
    else if (direction == "left")
      character.horizontal--;

    plot[character.vertical][character.horizontal] = character.avatar;

    printPlot(plot, plotDimension);

    cout << endl;
    cout << "You moved " << steps << " steps " << direction << "wards." << endl;

    sleep(1);
    if (i < steps - 1) {
    	clearscreen();
    }
	}
}