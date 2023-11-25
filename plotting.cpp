#include "players.h"
#include "shop.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <stdlib.h>
#include <unistd.h>
#include <chrono>
#include <thread>

using namespace std;

// Clear screen function that we will use
void clearscreen() {
    system("cls||clear");
}

// Read the text file size
void readTextDimensions (int & rowSize, int & columnSize, string filename) {
  ifstream fin;
  string row;
  columnSize = 0;

  // Opens map text file, then returns row and column size using pass by reference
  fin.open(filename.c_str());
  if (fin.fail()) {
    cout << "Error when loading text file." << endl;
    exit(1);
  }

  while (getline(fin, row)) {
    columnSize = row.length();
    rowSize++;
  }

  fin.close();
}

// Transform content of text file into a 2D array
// Function will respond corresponding based on type of text file specified
void readTextToArray (string **& array, int rowLength, int columnLength, string filename, string type) {
  ifstream fin;
  fin.open(filename.c_str());

  if (fin.fail()) {
    cout << "Error when loading text file." << endl;
    exit(1);
  }

  int arrayRow = 0, arrayColumn = 0;
  string row, textChar;
  
  // Obtain content of text file line by line
  while (getline(fin, row)) {
    // Reads every single character and input to array
    for (int i = 0; i < columnLength; ++i){
      textChar = row.substr(i, 1);  
      array[arrayRow][i] = textChar; 
    }
    arrayRow++;
  }

  // Calculates player spawn point if the type of text file is maze 
  if (type == "maze") {
    int playerSpawnRow = rowLength / 2;
    int playerSpawnColumn = columnLength / 2;
    
    playerObject character = playerObject(playerSpawnRow, playerSpawnColumn, true);
    array[playerSpawnRow][playerSpawnColumn] = character.avatar;
  }
  fin.close();
}

// Function to transform a text file into 2D array using previous functions
string ** initPlot (string filename, string type, int & rowSize, int & columnSize, string difficulty) {
  rowSize = 0, columnSize = 0;
  readTextDimensions(rowSize, columnSize, filename);

  string ** plot = new string * [rowSize];

  for (int i = 0; i < rowSize; ++i)
    plot[i] = new string [columnSize];
  
  readTextToArray(plot, rowSize, columnSize, filename, type);

  if (type == "maze") {
    int numObstacles = 0;

    // Determine the percentage of obstacles and teleportation portals based on the difficulty level
    if (difficulty == "easy") {
      numObstacles = rowSize * columnSize / 40;
    }
    else if (difficulty == "medium") {
      numObstacles = rowSize * columnSize / 30;
    }
    else if (difficulty == "hard") {
      numObstacles = rowSize * columnSize / 20;
    }

    for (int k = 0; k < numObstacles; ++k){
	    int row = rand() % rowSize;
	    int col = rand() % columnSize;

      if (plot[row][col] != "*" && plot[row][col] != "☠" && plot[row][col] != "|" && plot[row][col] != "-" && plot[row][col] != "☺"){
        int obstacleType = rand() % 2;

        if (obstacleType == 0)
	  	    plot[row][col] = "#"; // Obstacle character

        else if (obstacleType == 1)
	        plot[row][col] = "T"; // Teleportation portal character
	    }
    }
  }
  return plot; 
}

// Function to release memory slots occupied by dynamic array
void deleteArray (string **& array, int rowSize){
  for (int i = 0; i < rowSize; ++i) {
    delete [] array[i];
  }
  delete [] array;
}

// Select maze text files based on player specified difficulty
string selectPlot (string difficulty) {
  string map;
  if (difficulty == "easy") {
    map = "maze1.txt"; 
  }
  else if (difficulty == "medium") {
    map = "maze2.txt";
  }
  else if (difficulty == "hard") {
    map = "maze3.txt";
  }
  else {
    sleep(1);
    clearscreen();
    cout << "Invalid Difficulty!" << endl;
    return NULL;
  }
  return map;
}

// Function to randomize exit location
string randomExit () {
  srand(time(NULL));
  int randomization = rand() % 4;
  string exitPoint;
  switch (randomization){
    case 0:
      return "1";
    case 1:
      return "2";
    case 2:
      return "3";
    case 3:
      return "4";
    }
  return "4";
}

// Function to print a 2D array
void printPlot (string ** array, int rowSize, int columnSize, string exitPoint, bool fixPosition) {
  cout << endl;

  if (exitPoint == "1") {
    cout << "Escape the maze through the 1st exit!" << endl;
  }
  else if (exitPoint == "2") {
    cout << "Escape the maze through the 2nd exit!" << endl;
  }
  else if (exitPoint == "3") {
    cout << "Escape the maze through the 3rd exit!" << endl;
  }
  else if (exitPoint == "4") {
    cout << "Escape the maze through the 4th exit!" << endl;
  }

  for (int i = 0; i < rowSize; ++i) {
    for (int j = 0; j < columnSize; ++j) {
      cout << array[i][j];
    }
    cout << endl;
  }
  
  if (fixPosition == true)
    cout << "Returning to player to the previous position..." << endl;
}

// Calculate the spawn point of the player, which is the middle of the map
void calcPlayerSpawn (int & rowSize, int & columnSize) {
  rowSize /= 2;
  columnSize /= 2;
}

void moveAnimation (string **plot, int steps, playerObject& character, string direction, int rowSize, int columnSize, int coin, int timeLimit, bool & win, string exitPoint) {
  clearscreen();

  printPlot(plot, rowSize, columnSize, exitPoint); 
  this_thread::sleep_for(chrono::milliseconds(350));
  clearscreen();

  // If bump into obstacles let's say 3 times then player loses the game
  int bumps = 0;
  int maxBumps = 3;

  for (int i = 0; i < steps; ++i) {
    plot[character.vertical][character.horizontal] = ' ';

    // Boolean values for status checking are reset every iteration
    bool obstacleHit = false;
    bool teleportHit = false;

    // Store the the obstacle if we hit one
    string obstacle;

    // Track the previous position of the character before bumping into the obstacle
    int prevVertical = character.vertical;
    int prevHorizontal = character.horizontal;

    if (direction == "up")
      --character.vertical;
    else if (direction == "down")
      ++character.vertical;
    else if (direction == "right")
      ++character.horizontal;
    else if (direction == "left")
      --character.horizontal;

    // Checks if player hits an obstacle
    if (plot[character.vertical][character.horizontal] == "*" || plot[character.vertical][character.horizontal] == "|" || plot[character.vertical][character.horizontal] == "-"){
	    clearscreen();
	    cout << "You hit an obstacle!" << endl;
	    bumps++;

	    if (bumps >= maxBumps){
        win = false;
		    return;
	    }
	    sleep(1);

	    obstacleHit = true;
      obstacle = plot[character.vertical][character.horizontal];

      clearscreen();
    }
    
    // Checks if player encounters a teleporter
    else if (plot[character.vertical][character.horizontal] == "T"){
	    clearscreen();
      cout << "You encountered a teleporter" << endl;
      sleep(2);
	    teleportHit = true;
      // break;
    }

    // Checks if player encounters a shop
    else if (plot[character.vertical][character.horizontal] == "$"){
	    cout << "You have encountered a shop" << endl;
	    sleep(1);
      cout << "Do you want to visit it? (yes/no) ";
	    string answer;
	    cin >> answer;

	    if (answer == "yes") {
	      visiting_shop(coin, timeLimit, bumps, maxBumps, exitPoint);
	      // break;
      }
      else if (answer == "no") {
        clearscreen();
      }
    }
    else if (plot[character.vertical][character.horizontal] == exitPoint){
      win = true;
      return;
    }

    plot[character.vertical][character.horizontal] = character.avatar;
    printPlot(plot, rowSize, columnSize, exitPoint, obstacleHit); 

    cout << endl;
    if (!obstacleHit)
      cout << "You moved " << steps << " steps " << direction << "wards." << endl;

    this_thread::sleep_for(chrono::milliseconds(500));

    if (i < steps - 1 && !obstacleHit) {
    	clearscreen();
    }

    // Makes the player go back to previous position once hit the obstacle
    if (obstacleHit) {

      // Restores the obstacle
      plot[character.vertical][character.horizontal] = obstacle;

      // Restores the player's previous position
	    character.vertical = prevVertical;
	    character.horizontal = prevHorizontal;
	    plot[character.vertical][character.horizontal] = character.avatar;

      // Updates the plot
      this_thread::sleep_for(chrono::milliseconds(700));

      clearscreen();
      printPlot(plot, rowSize, columnSize,  exitPoint, obstacleHit);

      this_thread::sleep_for(chrono::milliseconds(1200));

      clearscreen();
      printPlot(plot, rowSize, columnSize, exitPoint);

      return;
    }
    
    // Teleports the player to a random position in the maze 
    if (teleportHit) {
      int teleportRow = rand() % rowSize;
	    int teleportCol = rand() % columnSize;
      
	    while (plot[teleportRow][teleportCol] != "*" && plot[teleportRow][teleportCol] != "☠" && plot[teleportRow][teleportCol] != "|" && plot[teleportRow][teleportCol] != "-" && plot[teleportRow][teleportCol] != "☺"){
		    teleportRow = rand() % rowSize;
        teleportCol = rand() % columnSize;
	    }
	    character.vertical = teleportRow;
	    character.horizontal = teleportCol;
	    plot[character.vertical][character.horizontal] = character.avatar;
    }
  }
}
