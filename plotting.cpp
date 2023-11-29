#include "players.h"
#include "shop.h"
#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <cstdlib>
#include <ctime>
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
	  
    srand(time(0));

    int cornerDistance = 5; //try not to make obstacles near the exit (not within 5 units)

    for (int k = 0; k < numObstacles; ++k) {
       int row, col;
       bool validPosition = false; //keep obstacles 

     while (!validPosition) {
          row = rand() % (rowSize - 1);
          col = rand() % (columnSize -1);

       //First check if it is not on maze properties
       if (plot[row][col] != "*" && plot[row][col] != "☠" && plot[row][col] != "|" && plot[row][col] != "-" && plot[row][col] != "☺") {
           validPosition = true;

      // Check if the position is within the corner distance
          if (row <= cornerDistance || row >= rowSize - cornerDistance - 1 || col <= cornerDistance || col >= columnSize - cornerDistance - 1) {
              validPosition = false;
          }
       }
     }
     int obstacleType = rand() % 2;

     if (obstacleType == 0){
       plot[row][col] = "#"; // Obstacle character
     }
     else if (obstacleType == 1){
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
    //try to use maze2.txt to avoid file loading error
  else if (difficulty == "hard") {
    map = "maze2.txt";
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
    cout << "Goal: Escape the maze through the 1st exit!" << endl;
  }
  else if (exitPoint == "2") {
    cout << "Goal: Escape the maze through the 2nd exit!" << endl;
  }
  else if (exitPoint == "3") {
    cout << "Goal: Escape the maze through the 3rd exit!" << endl;
  }
  else if (exitPoint == "4") {
    cout << "Goal: Escape the maze through the 4th exit!" << endl;
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
