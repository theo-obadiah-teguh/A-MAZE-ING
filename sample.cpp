#include <iostream>
#include <iomanip>
#include <string>
#include <stdlib.h>
#include <unistd.h>
using namespace std;

struct playerObject {
  int vertical; 
  int horizontal; 
  char avatar = 'O';

  playerObject(int vertSpawn, int horiSpawn) {
    vertical = vertSpawn;
    horizontal = horiSpawn;
  }
};

const int plotHeight = 31;
const int plotWidth = 31;

string Plot [plotHeight][plotWidth];
const int spawnPoint = 15; // Middle of the plot is the starting point

void createPlot () {
  for(int i = 0; i < plotHeight; i++) {
    for(int j = 0; j < plotWidth; j++) {
      if (i == spawnPoint && j == spawnPoint) {
        Plot[i][j] = "O";
      }
      else {
        Plot[i][j] = "*";
      }
    }
  }
}

void printPlot() {
  string result = "";

  for(int i = 0; i < plotHeight; i++) {
    string line = "";
    for(int j = 0; j < plotWidth; j++) {
      line += Plot[i][j];
    }
    result = result + line + '\n';
    }
    cout << result;
}

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