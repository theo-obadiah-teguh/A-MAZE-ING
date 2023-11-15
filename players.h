// searchword.h
#ifndef PLAYERS_H
#define PLAYERS_H

struct playerObject {
  int vertical; 
  int horizontal; 
  char avatar = 'U';

  // Declaring the struct with two integer arguments, i.e the spawn location of a player
  playerObject(int vertSpawn, int horiSpawn) {
    vertical = vertSpawn;
    horizontal = horiSpawn;
  }
};

// Function to animate character movement
void moveCharacter(int steps, playerObject& character, string direction);

#endif