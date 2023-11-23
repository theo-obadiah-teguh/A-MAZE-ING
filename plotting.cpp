#include "players.h"
#include "shop.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

// Clear screen function that we will use
void clearscreen() {
    system("cls||clear");
}

// Select maze text files based on player specified difficulty
string SelectPlot (string difficulty){
  string map;
  if (difficulty == "easy") {
    map = "maze1.txt"; 
  }
  else if (difficulty == "medium") {
    map = "maze1.txt";
  }
  else if (difficulty == "hard") {
    map = "maze1.txt";
  }
  else {
    sleep(1);
    clearscreen();
    cout << "Invalid Difficulty!" << endl;
    return NULL;
  }
  return map;
}

// Dynamically create 2D arrays for the plots based on the desired difficulty level
string ** initPlot (string difficulty, int& plotDimension) {
  if (difficulty == "easy") {
    plotDimension = 31;
    string **plot = new string*[plotDimension];
    for (int i = 0; i < plotDimension; ++i) {
      plot[i] = new string[plotDimension];
    }
    return plot;
  }
  else if (difficulty == "medium") {
    plotDimension = 41;
    string **plot = new string*[plotDimension];
    for (int i = 0; i < plotDimension; ++i) {
      plot[i] = new string[plotDimension];
    }
    return plot;
  }
  else if (difficulty == "hard") {
    plotDimension = 51;
    string **plot = new string*[plotDimension];
    for (int i = 0; i < plotDimension; ++i) {
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
void calcPlayerSpawn(int &row_size, int &column_size){
  row_size /= 2;
  column_size /= 2;
}

// Load in the characters that form the maze, from the .txt file to the array
void loadPlot(string **plot, int plotDimension, int spawnPoint) {
  for(int i = 0; i < plotDimension; ++i) {
    for(int j = 0; j < plotDimension; ++j) {
      if (i == spawnPoint && j == spawnPoint) {
        plot[i][j] = "☺";
      }
      else {
        plot[i][j] = "*";
      }
    }
  }

 // Adding obstacles in the maze through randomization (making it 15% of the maze) using "#" for obstacle and "T" for teleportation
  int numObstacles = plotDimension * plotDimension * 0.15;
  for (int k = 0; k < numObstacles; ++k){
	  int row = rand() % plotDimension;
	  int col = rand() % plotDimension;
          if (plot[row][col] != "☺" && plot[row][col] != "☠"){
                int obstacleType = rand() % 2;
                if (obstacleType == 0){
		  plot[row][col] = "#"; //Obstacle
		}
                else if (obstacleType == 1){
	          plot[row][col] = "T"; //Teleportation
                }
	  }
  }
}

void moveAnimation(string **plot, int steps, playerObject& character, string direction, int row_size, int column_size, int coin, int time_limit, bool &win) { // Use & to actually edit the struct
  clearscreen();

  // Track the previous position of the character before bumping into the obstacle
  int prevVertical = character.vertical;
  int prevHorizontal = character.horizontal;
  bool obstacleHit = false;
  bool teleportHit = false;
  bool shopHit = false;

  // If bump into obstacles let's say 3 times then player loses the game
  int bumps = 0;
  int maxBumps = 3;

  for(int i = 0; i < steps; ++i) {
    plot[character.vertical][character.horizontal] = ' ';

    if (direction == "up")
      --character.vertical;
    else if (direction == "down")
      ++character.vertical;
    else if (direction == "right")
      ++character.horizontal;
    else if (direction == "left")
      --character.horizontal;

    // Check if player hits an obstacle
    if (plot[character.vertical][character.horizontal] == "*" || plot[character.vertical][character.horizontal] == "|"){
	    clearscreen();
	    cout << "You hit an obstacle!" << endl;
	    bumps++;
	    if (bumps >= maxBumps){
		    cout << "You lost the game" << endl;
		    exit(0);
		    // Add option to restart the game and quit the game
		    // Aryaman will add a gameover function that will direct to a gameover screen
		    return;
	    }
	    sleep(2);
	    obstacleHit = true;
	    // break;
    }
    
    //Check if player encounters a teleporter
    else if (plot[character.vertical][character.horizontal] == "T"){
	clearscreen();
        cout << "You encountered a teleporter" << endl;
        sleep(2);
	teleportHit = true;
        //break;
    }

    else if (plot[character.vertical][character.horizontal] == "$"){
	cout << "You have encountered a shop" << endl;
	sleep(2);
        cout << "Do you want to visit there? (yes/no)" << endl;
	string answer;
	cin >> answer;
	if (answer == "yes"){
	  visiting_shop(coin, time_limit, bumps, maxBumps);
	 // break;
	  }
    }
    else if (plot[character.vertical][character.horizontal] == "@"){
        win = true;
        break;
    }
	    
    plot[character.vertical][character.horizontal] = character.avatar;
    print_plot(plot, row_size, column_size); 

    cout << endl;
    cout << "You moved " << steps << " steps " << direction << "wards." << endl;

    sleep(1);
    if (i < steps - 1) {
    	clearscreen();
    }

    // Make player go back to previous position once hit the obstacle
    if (obstacleHit){
	    character.vertical = prevVertical;
	    character.horizontal = prevHorizontal;
	    plot[character.vertical][character.horizontal] = character.avatar;
    }
    
    //Make player move to a random position on the maze 
    if (teleportHit) {
            int teleportRow = rand() % row_size;
	    int teleportCol = rand() % column_size;
	    while (plot[teleportRow][teleportCol] != "*" && plot[teleportRow][teleportCol] != "☠" && plot[teleportRow][teleportCol] != "|" && plot[teleportRow][teleportCol] != "☺"){
		    teleportRow = rand() % row_size;
                    teleportCol = rand() % column_size;
	    }
	    character.vertical = teleportRow;
	    character.horizontal = teleportCol;
	    plot[character.vertical][character.horizontal] = character.avatar;
    }
    
  }
}
