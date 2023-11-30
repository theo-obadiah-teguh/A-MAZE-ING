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
  int eatPoints;
};

// Calculates the player's spawning point
void calcPlayerSpawn (int & rowSize, int & columnSize);

// Function to print the player's current health points and coins
void printPlayerStats (playerObject player);

// Function to animate a character's movement
void movePlayer (string ** plot, int steps, playerObject& character, string direction, int rowSize, int columnSize, int timeLimit, bool & win, string exitPoint, int & monsterCount, int & monsterHunt);

#endif
