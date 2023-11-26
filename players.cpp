#include "players.h"
#include "plotting.h"
#include <unistd.h>
#include <chrono>
#include <thread>
using namespace std;

// Calculate the spawn point of the player, which is the middle of the map
void calcPlayerSpawn (int & rowSize, int & columnSize) {
  rowSize /= 2;
  columnSize /= 2;
}

// Function to print the player's current health points and coins
void printPlayerStats (playerObject player) {
  cout << "HP: " << player.health << "   Coins: " << player.coins << endl;
  cout << endl;
}

// Function to animate the player's movement
void movePlayer (string ** plot, int steps, playerObject& character, string direction, int rowSize, int columnSize, int timeLimit, bool & win, string exitPoint) {
  clearscreen();

  printPlot(plot, rowSize, columnSize, exitPoint);
  printPlayerStats(character);

  string directionLiteral;
  if (direction == "w") {
    directionLiteral = "up";
  }
  else if (direction == "a") {
    directionLiteral = "left";
  }
  else if (direction == "s") {
    directionLiteral = "down";
  }
  else if (direction == "d") {
    directionLiteral = "right";
  }

  cout << "You moved " << steps << " step(s) " << directionLiteral << "wards." << endl;

  this_thread::sleep_for(chrono::milliseconds(500));
  clearscreen();

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

    if (direction == "w")
      --character.vertical;
    else if (direction == "s")
      ++character.vertical;
    else if (direction == "d")
      ++character.horizontal;
    else if (direction == "a")
      --character.horizontal;

    // Checks if player hits an obstacle
    if (plot[character.vertical][character.horizontal] == "#" || plot[character.vertical][character.horizontal] == "*" || plot[character.vertical][character.horizontal] == "|" || plot[character.vertical][character.horizontal] == "-"){
      sleep(1);
	    clearscreen();

	    obstacleHit = true;
      obstacle = plot[character.vertical][character.horizontal];

      // Obstacles are destructible walls, they exhaust the player (-2 HP)
      // Walls do more damage (-5 HP)

      if (obstacle == "#") {
        cout << "You encountered an obstacle." << endl;
        sleep(1);
        cout << "You become exhausted after overcoming it. (-2 HP)" << endl;
        sleep(1);
        character.health -= 2;
        cout << "You now have " << character.health << " HP." << endl;
        sleep(2);
      }
      else {
        cout << "You bumped into a wall! (-5 HP)" << endl;
        sleep(1);
        character.health -= 5;
        cout << "You now have " << character.health << " HP." << endl;
        sleep(2);
      }

      if (character.health <= 0) {
		    return;
	    }

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
	      visitShop(timeLimit, character, exitPoint);
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
    printPlot(plot, rowSize, columnSize, exitPoint, obstacleHit && obstacle != "#");
    printPlayerStats(character);

    if (!obstacleHit || obstacle == "#") {
      cout << "You moved " << steps << " step(s) " << directionLiteral << "wards." << endl;
    }

    this_thread::sleep_for(chrono::milliseconds(500));

    if (i < steps - 1 && !obstacleHit) {
    	clearscreen();
    }

    // Makes the player go back to previous position once hit the obstacle
    if (obstacleHit && obstacle != "#") {

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
      printPlayerStats(character);

      this_thread::sleep_for(chrono::milliseconds(1200));

      clearscreen();
      printPlot(plot, rowSize, columnSize, exitPoint);
      printPlayerStats(character);

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
