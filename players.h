#ifndef PLAYERS_H
#define PLAYERS_H
#include <string>
using namespace std;
struct playerObject {
  int vertical; 
  int horizontal; 
  string avatar;

  int health;
  int coins;

  int jumpPoints;

  // Declaring the struct with two integer arguments, i.e the spawn location of a player
  // If we want to initialize a player, set type to true
  // If we want to initialize a ghost, set type to false

  playerObject(int vertSpawn, int horiSpawn, bool type) {
    vertical = vertSpawn;
    horizontal = horiSpawn;
    if (type == true)
      avatar = "☺";
    else
      avatar = "☠";
  }
};

// Calculates the player's spawning point
void calcPlayerSpawn (int & rowSize, int & columnSize);

// Function to print the player's current health points and coins
void printPlayerStats (playerObject player);

// Function to animate a character's movement
void movePlayer (string ** plot, int steps, playerObject& character, string direction, int rowSize, int columnSize, int timeLimit, bool & win, string exitPoint, int & monsterCount, int & monsterHunt);

#endif
