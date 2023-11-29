#include "plotting.h"
#include "players.h"
#include "aesthetics.h"
#include <iostream>
#include <unistd.h>
#include <string>
#include <cctype>
#include "monster.h"
#include <chrono>

using namespace std;
using namespace std::chrono;

int main() {
  clearscreen();

  welcomeAnimation();

  // Selecting a desired difficulty level
  string difficulty;
  cout << "Please choose a difficulty level -> (easy, medium, hard): ";
  cin >> difficulty;
  string map = selectPlot(difficulty);

  // Initialize memory allocation and playerObject
  int rowSize = 0, columnSize = 0, timeLimit = 180, monsterHunt;
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
  player.coins = 150;
  player.eatPoints = 5;

  clearscreen();

  // Initialize monster vector
  int monsterCount = 0;
  monsterNo(difficulty, monsterCount);
    
  createMonsters(monsterCount);
  init(rowSize, columnSize, myPlot, monsterCount);
    
    
  printPlot(myPlot, rowSize, columnSize, exitPoint);
  printPlayerStats(player);
  cout << "You find yourself in the center of a dungeon maze!" << endl;
  sleep(2);

  string prevDirection;
  bool firstJourney = true;

// Start the timer
  auto startTime = steady_clock::now();

  while (true) {
    string direction;
    int steps;

    if (firstJourney) {
      cout << "Please ENTER the 'w', 'a', 's', 'd' keys to choose a direction." << endl;
      cout << "Which direction do you want to go? (ENTER 'q' to quit) ";
      cin >> direction;

      if (direction == "W") {
        direction = "w";
      }
      else if (direction == "A") {
        direction = "a";
      }
      else if (direction == "S") {
        direction = "s";
      }
      else if (direction == "D") {
        direction = "d";
      }
      else if (direction == "Q") {
        direction = "q";
      }

      if (direction == "q") {
        startMenu();
        break;
      }

      if (direction != "w" && direction != "a" && direction != "s" && direction != "d") {
        clearscreen();
        printPlot(myPlot, rowSize, columnSize, exitPoint);
        printPlayerStats(player);
        cout << "You find yourself in the center of a dungeon maze!" << endl;
        continue;
      }

      cout << "How far will you go? (ENTER a number)";
      cin >> steps;

      firstJourney = false;
    }
    else {
      //cout << "Which direction do you want to go? ";
        cout << "Please ENTER the 'w', 'a', 's', 'd' keys to choose a direction." << endl;
        cout << "Which direction do you want to go? (ENTER 'q' to quit) ";
      cin >> direction;

      if (direction == "W") {
        direction = "w";
      }
      else if (direction == "A") {
        direction = "a";
      }
      else if (direction == "S") {
        direction = "s";
      }
      else if (direction == "D") {
        direction = "d";
      }
      else if (direction == "Q") {
        direction = "q";
      }

      if (direction == "q") {
        startMenu();
        break;
      }

      if (direction != "w" && direction != "a" && direction != "s" && direction != "d") {
        clearscreen();
        printPlot(myPlot, rowSize, columnSize, exitPoint);
        printPlayerStats(player);
        continue;
      }

      cout << "How far will you go now? ";
      cin >> steps;
    }

// Calculate the elapsed time
    auto currentTime = steady_clock::now();
    auto elapsedTime = duration_cast<seconds>(currentTime - startTime).count();

    // Display the elapsed time
    cout << "Time: " << elapsedTime << " seconds" << endl;

    monsterHunt = 0;
      
    movePlayer(myPlot, steps, player, direction, rowSize, columnSize, timeLimit, win, exitPoint, monsterCount, monsterHunt);
    prevDirection = direction;
    //move monster after player move
    monsterDir(player)
    monsterSteps(myPlot, rowSize, columnSize);
    clearscreen();
    printPlot(myPlot, rowSize, columnSize, exitPoint);

    if (player.health <= 0) {
      defeatAnimation();
      break;
    }
    else if (win == true){
      victoryAnimation();
      break;

    }
  }
}
