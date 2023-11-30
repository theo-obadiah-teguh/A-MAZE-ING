#include "aesthetics.h"
#include "plotting.h"
#include "players.h"
#include "monster.h"
#include <iostream>
#include <unistd.h>
#include <string>
#include <cctype>
#include <chrono>

using namespace std;
using namespace std::chrono;

/* 
Function to display welcome animation or menu screen depending on whether it is the first try. 
It will then start the maze game. 
*/

void startGame(bool FirstTry) {
  clearscreen();
  
  if(FirstTry) {
    welcomeAnimation();
  }
  else {
    startMenu();
  }


  string difficultyInput, difficulty;

  // Selecting a desired difficulty level
  while (true) {
    clearscreen();
    cout << "Please choose a difficulty level (1-3):" << endl;
    cout << "1: Easy" << endl;
    cout << "2: Medium" << endl;
    cout << "3: Hard" << endl;
    cout << "Your Input: ";
    cin >> difficultyInput;

    if (difficultyInput == "1") {
      difficulty = "easy";
      break;
    }
    else if (difficultyInput == "2") {
      difficulty = "medium";
      break;
    }
    else if (difficultyInput == "3") {
      difficulty = "hard";
      break;
    }
  }

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
  
  playerObject player = {playerSpawnRow, playerSpawnColumn, "☺", 100, 150, 5};
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

  // Ask for player input and continue the game repeatedly until the player press 'q'
  
  int steps; 

  while (true) {
    string direction;

    // Describe how to control movement when the player enters the maze. Then ask player for direction to move him/her
    
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
        deleteArray(myPlot, rowSize);
        deleteMonsters(monsterCount);
        break;
      }

      if (direction != "w" && direction != "a" && direction != "s" && direction != "d") {
        clearscreen();
        printPlot(myPlot, rowSize, columnSize, exitPoint);
        printPlayerStats(player);
        cout << "You find yourself in the center of a dungeon maze!" << endl;
        continue;
      }

      string stepsInput;

      cout << "How far will you go now? ";
      cin >> stepsInput;

      // Check if input is actually a number
      if (!all_of(stepsInput.begin(), stepsInput.end(), ::isdigit)) {
        clearscreen();
        printPlot(myPlot, rowSize, columnSize, exitPoint);
        printPlayerStats(player);
        continue;
      }
  
      // Convert string input to integer
      steps = stoi(stepsInput);

      firstJourney = false;
    }
    else {
        cout << "Please ENTER the 'w', 'a', 's', 'd' keys to choose a direction. " << endl;
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
        deleteArray(myPlot, rowSize);
        deleteMonsters(monsterCount);
        break;
      }

      if (direction != "w" && direction != "a" && direction != "s" && direction != "d") {
        clearscreen();
        printPlot(myPlot, rowSize, columnSize, exitPoint);
        printPlayerStats(player);
        continue;
      }

      string stepsInput;
      cout << "How far will you go now? ";
      cin >> stepsInput;

      // Check if input is actually a number
      if (!all_of(stepsInput.begin(), stepsInput.end(), ::isdigit)) {
        clearscreen();
        printPlot(myPlot, rowSize, columnSize, exitPoint);
        printPlayerStats(player);
        continue;
      }

      // Convert string input to integer
      steps = stoi(stepsInput);
    }

    // Move the player based on selected direction and move monster towards the player at each stage
    
    monsterHunt = 0;
      
    movePlayer(myPlot, steps, player, direction, rowSize, columnSize, timeLimit, win, exitPoint, monsterCount, monsterHunt);
    prevDirection = direction;
    
    // Moves monster after the player moves
    
    monsterDir(player);
    monsterSteps(myPlot, rowSize, columnSize);
    clearscreen();
    printPlot(myPlot, rowSize, columnSize, exitPoint);
    printPlayerStats(player);

    // Delete dynamic array and display defeat anaimation when the player loses
    
    if (player.health <= 0) {
      defeatAnimation();
      deleteArray(myPlot, rowSize);
      deleteMonsters(monsterCount);
      break;
    }

    // Delete dynamic array and display victory anaimation when player win the game
      
    else if (win == true){
      victoryAnimation();
      deleteArray(myPlot, rowSize);
      deleteMonsters(monsterCount);
      break;
    }
  }
}

/* 
Main function that will keep calling startGame. 
There is an exit function in the menu function so there will not be infinite loops. 
*/

int main(){
  bool FirstTry = true; 
  while (true) {
    startGame(FirstTry);
    FirstTry = false;
  }
}
