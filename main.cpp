#include "plotting.h"
#include "players.h"
#include "aesthetics.h"
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
  clearscreen();

  welcomeAnimation();

  // Selecting a desired difficulty level
  string difficulty;
  cout << "Please choose a difficulty level -> (easy, medium, hard): ";
  cin >> difficulty;
  string map = selectPlot(difficulty);

  // Initialize memory allocation and playerObject
  int rowSize = 0, columnSize = 0, timeLimit = 180;
  bool win = false;

  // Initialize our maze plot
  string type = "maze";
  string ** myPlot = initPlot(map, type, rowSize, columnSize, difficulty);

  // Initialize the randomly assigned exit
  string exitPoint = randomExit();
  
  if (myPlot == NULL) {
    exit(1);
  }
  
  // Initialize player spawning point
  int playerSpawnRow = rowSize, playerSpawnColumn = columnSize;
  calcPlayerSpawn(playerSpawnRow, playerSpawnColumn);

  // Initialize main player object
  playerObject player = playerObject(playerSpawnRow, playerSpawnColumn, true);
  player.health = 100;
  player.coins = 60;

  clearscreen();

  printPlot(myPlot, rowSize, columnSize, exitPoint);
  printPlayerStats(player);
  cout << "You find yourself in the center of a dungeon maze!" << endl;
  sleep(2);
    
  bool firstJourney = true;
  while (true) {
    string direction;
    int steps;

    if (firstJourney) {
      cout << "Where do you want to go? ";
    }
    else {
      // cout << player.vertical << " " << player.horizontal << endl; //debug
      cout << "Where do you want to go next? ";
    }

    cin >> direction;

    if (firstJourney) {
      cout << "How far will you go? ";
      firstJourney = false;
    }
    else {
      cout << "How far will you go now? ";
    }
    cin >> steps;

    movePlayer(myPlot, steps, player, direction, rowSize, columnSize, timeLimit, win, exitPoint);

    if (player.health <= 0) {
      defeatAnimation();
      break;
    }
    else if (win == true){
      victoryAnimation();
      break;
    }
    
    string answer;
    cout << "Do you want to continue your journey? (yes/no) ";
    cin >> answer;

    if (answer == "no") {
      exitAnimation();
      break;
    }
  }
}
