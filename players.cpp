#include "plotting.h"
#include <iostream>
#include <stdlib.h>
#include <unistd.h>

struct playerObject {
  int vertical; 
  int horizontal; 
  char avatar = 'U';

  playerObject(int vertSpawn, int horiSpawn) {
    vertical = vertSpawn;
    horizontal = horiSpawn;
  }
};

void moveCharacter(int steps, playerObject& character, string direction) { // Use & to actually edit the struct
  system("clear");
  for(int i = 0; i < steps; i++) {
    Plot[character.vertical][character.horizontal] = '*';

    if (direction == "up")
      character.vertical--;
    else if (direction == "down")
      character.vertical++;
    else if (direction == "right")
      character.horizontal++;
    else if (direction == "left")
      character.horizontal--;

    Plot[character.vertical][character.horizontal] = character.avatar;

    printPlot();

    cout << endl;
    cout << "You moved " << steps << " steps " << direction << "wards." << endl;

    sleep(1);
    if (i < steps - 1) {
    	system("clear"); // Use "cls" for Linux (IMPORTANT!)
    }
	}
}