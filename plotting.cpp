#include <iostream>
#include <string>
using namespace std;

const int plotHeight = 31;
const int plotWidth = 31;

string Plot [plotHeight][plotWidth];
const int spawnPoint = 15; // Middle of the plot is the starting point

void createPlot() {
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