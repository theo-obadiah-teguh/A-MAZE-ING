#include "players.h"
#include "plotting.h"
#include "monster.h"
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
  cout << "HP: " << player.health << "   Coins: " << player.coins << "   Eat: " << player.eatPoints << endl;
  cout << endl;
}

// Function to animate the player's movement
void movePlayer (string ** plot, int steps, playerObject& character, string direction, int rowSize, int columnSize, int timeLimit, bool & win, string exitPoint, int & monsterCount, int & monsterHunt) {
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
    if (plot[character.vertical][character.horizontal] == "#" || plot[character.vertical][character.horizontal] == "*" || plot[character.vertical][character.horizontal] == "|" || plot[character.vertical][character.horizontal] == "-" || plot[character.vertical][character.horizontal] == "☠"){
      sleep(1);
	    clearscreen();

	    obstacleHit = true;
      obstacle = plot[character.vertical][character.horizontal];

      // Obstacles are destructible walls, they exhaust the player (-2 HP)
      // Walls do more damage (-5 HP)
      // If player hits monster, the damage would be even higher (-50 HP)

      if (obstacle == "#") {
        cout << "You encountered an obstacle." << endl;
        sleep(1);
        cout << "You become exhausted after overcoming it. (-2 HP)" << endl;
        sleep(1);
        character.health -= 2;
        cout << "You now have " << character.health << " HP." << endl;
        sleep(2);
      }
      else if (obstacle == "☠") {
        cout << "You bumped into a monster!" << endl;
        sleep(1);
        cout << "You have fought it off, but you are heavily injured. (-50 HP)" << endl;
        sleep(1);
        character.health -= 50;
          huntMonster(plot);
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
    else if (plot[character.vertical][character.horizontal] == "T") {
      clearscreen();
      cout << "You encountered a teleporter" << endl;
      sleep(2);
      cout << "Do you want to eat the teleporter? (yes/no) ";
      string answer;
      cin >> answer;
      if (answer == "yes") {
        // Check if the player has enough eat points
        if (character.eatPoints > 0) {
          // Decrement the eat points
          character.eatPoints--;

          // Clear the current position
          plot[character.vertical][character.horizontal] = ' ';

          // Update the plot with the new position
          plot[character.vertical][character.horizontal] = character.avatar;

          // Print the updated plot and player stats
          clearscreen();
          printPlot(plot, rowSize, columnSize, exitPoint);
          printPlayerStats(character);

          // Display the eat message
          cout << "You ate the teleporter!" << endl;

          // Wait for a moment before clearing the screen
          this_thread::sleep_for(chrono::milliseconds(1000));
          clearscreen();
	      }
        else {
          cout << "You don't have enough points to eat the teleporter." << endl;
	        teleportHit = true;
	      }
      }
      else {  
      	 teleportHit = true;
      }
    }

    // Checks if player encounters a shop
    else if (plot[character.vertical][character.horizontal] == "$") {
	    cout << "You have encountered a shop" << endl;
	    sleep(1);
      cout << "Do you want to visit it? (yes/no) ";
	    string answer;
	    cin >> answer;

	    if (answer == "yes") {
	      visitShop(monsterHunt, monsterCount, character, exitPoint);
	      for (int j = 0; j< monsterHunt; ++j){
		      huntMonster(plot);
	      }
	      clearscreen();
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
    printPlot(plot, rowSize, columnSize, exitPoint, obstacleHit && obstacle != "☠" && obstacle != "#"); 
    printPlayerStats(character);

    if (!obstacleHit || obstacle == "#" || obstacle == "☠") {
      cout << "You moved " << steps << " step(s) " << directionLiteral << "wards." << endl;
    }

    this_thread::sleep_for(chrono::milliseconds(500));

    if (i < steps - 1 && !obstacleHit) {
      clearscreen(); // DO NOT EDIT
    }

    // Makes the player go back to previous position once hit a wall
    if (obstacleHit && obstacle != "#" && obstacle != "☠") {

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

      //this_thread::sleep_for(chrono::milliseconds(1200));

      //clearscreen();
      //printPlot(plot, rowSize, columnSize, exitPoint);
      //printPlayerStats(character);
      break; // DO NOT DELETE. CRUCIAL PART
    }

    if (teleportHit) {
    // Store the teleporter's original position
    	int teleportRow = character.vertical;
    	int teleportCol = character.horizontal;

    // Set a constraint on how far the player can teleport
    	int maxDistance = 10;

    // Find a random empty position in the maze
    	int playerRow, playerCol;
    	do {
        	playerRow = teleportRow + (rand() % (2 * maxDistance + 1) - maxDistance);
        	playerCol = teleportCol + (rand() % (2 * maxDistance + 1) - maxDistance);

        // Check if the generated position is within the valid range of the maze
        	if (playerRow >= 0 && playerRow < rowSize && playerCol >= 0 && playerCol < columnSize) {
            // Check if the generated position is an empty space
            		if (plot[playerRow][playerCol] == " ") {
                		break;  // Exit the loop if an empty location is found
            		}
        	}
    	} while (true);

    // Move the player to the random empty position
    plot[character.vertical][character.horizontal] = " ";
    character.vertical = playerRow;
    character.horizontal = playerCol;
    plot[character.vertical][character.horizontal] = character.avatar;

    // Remove the teleporter from its original position
    plot[teleportRow][teleportCol] = " ";

    // Clear the screen and display the updated maze
    clearscreen();
    printPlot(plot, rowSize, columnSize, exitPoint);
    printPlayerStats(character);
    }
  }
}
