#include "plotting.h"
#include "players.h"
#include "aesthetics.h"
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <string>

using namespace std;

int main() {
  clearscreen();

  welcomeAnimation();

  string difficulty;
  cout << "Please choose a difficulty level -> (easy, medium, hard): ";
  cin >> difficulty;

  // Initialize memory allocation and playerObject
  int row_size = 0, column_size =0, coin = 60, time_limit = 180;
  bool win = false;
  string filename = "maze1.txt";
  array_size(row_size, column_size, filename);
  string map  = SelectPlot(difficulty);
  string type = "maze";
  string ** myPlot = create_plot(map, type, row_size, column_size);

  if (myPlot == NULL) {
    exit(1);
  }
  
  int spawn_row = row_size, spawn_column = column_size;
  calcPlayerSpawn(spawn_row, spawn_column);
  playerObject player = playerObject(spawn_row, spawn_column, true);

  clearscreen();

  print_plot(myPlot, row_size, column_size);
  cout << endl;
  sleep(2);

  cout << "You find yourself in the center of a dungeon maze!" << endl;
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

    moveAnimation(myPlot, steps, player, direction, row_size, column_size, coin, time_limit, win);
    if (win == true){
      victoryAnimation();
      break;
    }
    
    string answer;
    cout << "Do you want to continue your journey? (yes/no) ";
    cin >> answer;

    if (answer == "no") {
      exitAnimation();
      break;
    }
  }
}
