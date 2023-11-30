#include "players.h"
#include "monster.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

vector<monsterObject *> monster;
int monsterCount;

// Function to determine the number of monsters based on player selected difficulty
void monsterNo(string difficulty, int & monsterCount) {
  if (difficulty == "easy") {
    monsterCount = 1;
  }
  else if (difficulty == "medium") {
    monsterCount = 3;
  }
  else if (difficulty == "hard") {
    monsterCount = 5;
  }
}

// Function to add the monster objects into the vector
void createMonsters(int monsterCount) {
  for(int i = 0; i < monsterCount; ++i){
    monster.push_back(new monsterObject);
  }
}

// Function to delete all the monsters if the player quits
void deleteMonsters(int monsterCount) {
  for(int i = 0; i < monsterCount; ++i){
      monster.pop_back();
  }
}

// Function to remove a monster from the plot
void huntMonster(string ** myPlot, int & monsterCount){
  int location = monster.size();
  myPlot[monster[location - 1]->vertical_ax][monster[location - 1]->horizontal_ax] = " ";
  monster.pop_back();
  monsterCount--;
  return;
}

// Function to decide monster moving direction based on player location so that the monster will move towards the player
void monsterDir(playerObject player) {
  time_t _time = time(nullptr);
  srand(static_cast<unsigned>(_time));
    
  for (int i = 0; i < monster.size(); ++i) {
  	time_t _time = time(nullptr);

    // 1 is up, 2 is right, 3 is down, 4 is left
    if (monster[i]->vertical_ax - player.vertical <= 0 ) {
      if (monster[i]->horizontal_ax - player.horizontal >= 0) {
        monster[i]->direction = rand() % 2 + 3;
      } 
			else {
        monster[i]->direction=rand() % 2 + 2;
      }
    } 
		else {
      if (monster[i]->horizontal_ax - player.horizontal <= 0) {
        monster[i]->direction=rand() % 2 + 1;
      } 
			else {
        monster[i]->direction=(rand() % 2 == 0) ? 1 : 4;
      }
    }
  }
}

// Function to initialize monster position in the maze
void init(int rowSize, int columnSize, string ** myPlot, int monsterCount) {
  time_t _time = time(nullptr);
  srand(static_cast<unsigned>(_time));
  for (int i = 0; i < monsterCount; ++i) {
    monster[i]->vertical_ax = rand() % (rowSize - 2) + 1;
    monster[i]->horizontal_ax = rand() % (columnSize - 2) + 1;

    if (myPlot[monster[i]->vertical_ax][monster[i]->horizontal_ax] == " ") {
      myPlot[monster[i]->vertical_ax][monster[i]->horizontal_ax] = "☠";
    }
    else {
      if (myPlot[monster[i]->vertical_ax][monster[i]->horizontal_ax] != " ") {
      	monster[i]->vertical_ax -= 1;
        myPlot[monster[i]->vertical_ax][monster[i]->horizontal_ax] = "☠";
      }
      else {
        if (myPlot[monster[i]->vertical_ax][monster[i]->horizontal_ax] == "|" && myPlot[monster[i]->vertical_ax][monster[i]->horizontal_ax - 1] == "*" && myPlot[monster[i]->vertical_ax][monster[i]->horizontal_ax + 1] == " "){
          monster[i]->horizontal_ax += 1;
          myPlot[monster[i]->vertical_ax][monster[i]->horizontal_ax] = "☠";
        }
        else if (myPlot[monster[i]->vertical_ax][monster[i]->horizontal_ax] == "|" && myPlot[monster[i]->vertical_ax][monster[i]->horizontal_ax + 1] == "*" && myPlot[monster[i]->vertical_ax][monster[i]->horizontal_ax - 1] == " "){
          monster[i]->horizontal_ax -= 1;
          myPlot[monster[i]->vertical_ax][monster[i]->horizontal_ax] = "☠";
        }
        else {
          do {
            monster[i]->vertical_ax = rand() % rowSize;
            monster[i]->horizontal_ax = rand() % columnSize;
          } while(myPlot[monster[i]->vertical_ax][monster[i]->horizontal_ax] != " ");
        }
      }
    }
	}
}


// Check validity (make sure the ghost will not go out of boundary)
// 1st para  monster_count-> i

bool checkValid(int i, int & monsterSteps, string ** myPlot, int rowSize, int columnSize) {
	// **UNUSED CODE**
  // Iterate over all monsters
  // for (int i=0;i<monster_count;i++) {
	// updated plotdimension -> rowSize/columnSize

  // Vertical movement
	// Movement upwards
  if (monster[i]->direction == 1) {
    if (monster[i]->vertical_ax - monsterSteps >= 1) {
      for (int a = 0; a < monsterSteps; ++a) {
        /* if (myPlot[monster[i]->vertical_ax-1-a][monster[i]->horizontal_ax] == "|" || myPlot[monster[i]->vertical_ax-1-a][monster[i]->horizontal_ax] == "*") {
          monsterSteps++;
        } */
        if (myPlot[monster[i]->vertical_ax - 1 - a][monster[i]->horizontal_ax] != " ") {
          monsterSteps++;
        }
      }
      if (monster[i]->vertical_ax - monsterSteps >= 1) {
        return true;
      }
      else {
        return false;
      }
    }
  	else {
    	return false;
  	}
  }
	// Movement downwards
  else if (monster[i]->direction == 3) {
    if (monster[i]->vertical_ax + monsterSteps <= rowSize - 2) {
      for (int b = 0; b < monsterSteps; ++b) {
        /* if (myPlot[monster[i]->vertical_ax+1+b][monster[i]->horizontal_ax] == "|" || myPlot[monster[i]->vertical_ax+1+b][monster[i]->horizontal_ax] == "*") {
          monsterSteps++;
        } */
        if (myPlot[monster[i]->vertical_ax + 1 + b][monster[i]->horizontal_ax] != " ") {
            monsterSteps++;
    		}
      }
      if (monster[i]->vertical_ax + monsterSteps <= rowSize - 2) {
        return true;
      }
      else {
        return false;
      }
    }
    else {
      return false;
    }
	}
  // Horizontal movement
	// Movement rightwards
  else if (monster[i]->direction == 2) {
    if (monster[i]->horizontal_ax + monsterSteps <= columnSize - 2) {
    	for (int c = 0; c < monsterSteps; ++c) {
    	  /* if (myPlot[monster[i]->vertical_ax][monster[i]->horizontal_ax+1+c] == "*" || myPlot[monster[i]->vertical_ax][monster[i]->horizontal_ax+1+c] == "|") {
    	    monsterSteps++;
    	  } */
    	  if (myPlot[monster[i]->vertical_ax][monster[i]->horizontal_ax + 1 + c] != " ") {
    	    monsterSteps++;
				}
    	}
			if (monster[i]->horizontal_ax + monsterSteps <= columnSize - 2) {
    	  return true;
			}
    	else {
    		return false;
			}
    }
    else {
    	return false;
    }
  }
	// Movement leftwards
  else if (monster[i]->direction == 4) {
    if (monster[i]->horizontal_ax - monsterSteps >= 1) {
      for (int d = 0; d < monsterSteps; ++d) {
      	/* if (myPlot[monster[i]->vertical_ax][monster[i]->horizontal_ax-1-d] == "*" || myPlot[monster[i]->vertical_ax][monster[i]->horizontal_ax-1-d] == "|") {
          monsterSteps++;
        } */
        if (myPlot[monster[i]->vertical_ax][monster[i]->horizontal_ax - 1 - d] != " ") {
          monsterSteps++;
        }
      }
      if (monster[i]->horizontal_ax - monsterSteps >= 1) {
        return true;
      }
      else {
        return false;
      }
    }
    else {
      return false;
    }
  }
  return false;
}

// Function to determine how many steps the monster will take
void monsterSteps(string ** myPlot, int rowSize, int columnSize){
  time_t _time = time(nullptr);
  srand(static_cast<unsigned>(_time));

  for (int i = 0; i < monster.size(); ++i) {
    time_t _time = time(nullptr);
    int monsterSteps = rand() % 4 + 1;
    
    if (checkValid(i, monsterSteps, myPlot, rowSize, columnSize) == true) {
      // Move the monster
      if (monster[i]->direction == 1) {
        myPlot[monster[i]->vertical_ax][monster[i]->horizontal_ax] = " ";
        monster[i]->vertical_ax -= monsterSteps;
        myPlot[monster[i]->vertical_ax][monster[i]->horizontal_ax] = "☠";
      }
      else if (monster[i]->direction == 2) {
        myPlot[monster[i]->vertical_ax][monster[i]->horizontal_ax] = " ";
        monster[i]->horizontal_ax += monsterSteps;
        myPlot[monster[i]->vertical_ax][monster[i]->horizontal_ax] = "☠";
      }
      else if (monster[i]->direction == 3) {
        myPlot[monster[i]->vertical_ax][monster[i]->horizontal_ax] = " ";
        monster[i]->vertical_ax += monsterSteps;
        myPlot[monster[i]->vertical_ax][monster[i]->horizontal_ax] = "☠";
      }
      else {
        myPlot[monster[i]->vertical_ax][monster[i]->horizontal_ax] = " ";
        monster[i]->horizontal_ax -= monsterSteps;
        myPlot[monster[i]->vertical_ax][monster[i]->horizontal_ax] = "☠";
      }
    }
    else {
      // Call back function and try until all moves are valid
      do {
        monsterSteps = rand() % 4 + 1;
      } while (checkValid(i, monsterSteps, myPlot, rowSize, columnSize) == false);
    }  
  }
}
    

