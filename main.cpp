#include "plotting.h"
#include "players.h"
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <string>
using namespace std;

int main() {
  playerObject player = playerObject(spawnPoint, spawnPoint);
  createPlot();
    
  string distance;
  int movement;

  system("clear");

  cout << "Welcome to the game." << endl;
  sleep(2);

  cout << "You find yourself in the center of a maze!" << endl;
  cout << endl;
  sleep(2);

  printPlot();
  cout << endl;
  sleep(2);
    
  bool firstJourney = true;
  while (true) {
    if (firstJourney) {
      cout << "Where do you want to go? ";
    }
    else {
      // cout << player.vertical << " " << player.horizontal << endl; //debug
      cout << "Where do you want to go next? ";
    }

    cin >> distance;

    if (firstJourney) {
      cout << "How far will you go? ";
      firstJourney = false;
    }
    else {
      cout << "How far will you go now? ";
    }
    cin >> movement;

    moveCharacter(movement, player, distance);  
        
    string answer;
    cout << "Do you want to continue your journey? (yes/no) ";
    cin >> answer;

    if (answer == "no") {
      system("clear");
      cout << "See you next time, traveller!" << endl;
      sleep(2);
      break;
    }
  }
}