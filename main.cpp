#include "plotting.h"
#include "players.h"
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <string>

using namespace std;

int main() {
  system("clear");

  cout << "Welcome to the game." << endl;
  sleep(2);

  string difficulty;
  cout << "Please choose a difficulty level -> (easy, medium, hard): ";
  cin >> difficulty;

  // Initialize memory allocation and playerObject
  int plotDimension;
  string ** myPlot = initPlot(difficulty, plotDimension);

  if (myPlot == NULL) {
    exit(1);
  }

  int spawnPoint = calcPlayerSpawn(plotDimension);
  playerObject player = playerObject(spawnPoint, spawnPoint);

  system("clear");

  cout << "You find yourself in the center of a maze!" << endl;
  cout << endl;
  sleep(2);

  loadPlot(myPlot, plotDimension, spawnPoint);
  printPlot(myPlot, plotDimension);
  cout << endl;
  sleep(2);
    
  bool firstJourney = true;
  while (true) {
    string direction;
    int steps;

    if (firstJourney) {
      cout << "Where do you want to go? ";
    }
    else {
      // cout << player.vertical << " " << player.horizontal << endl; //debug
      cout << "Where do you want to go next? ";
    }

    cin >> direction;

    if (firstJourney) {
      cout << "How far will you go? ";
      firstJourney = false;
    }
    else {
      cout << "How far will you go now? ";
    }
    cin >> steps;

    moveAnimation(myPlot, steps, player, direction, plotDimension);  
        
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