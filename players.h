#ifndef PLAYERS_H
#define PLAYERS_H
#include <string>
using namespace std;
struct playerObject {
  int vertical; 
  int horizontal; 
  string avatar;

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

#endif