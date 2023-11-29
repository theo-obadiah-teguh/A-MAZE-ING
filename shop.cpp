#include "plotting.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <unistd.h>
using namespace std;

void purchaseOptions(int & monsterHunt, int & monsterCount, playerObject & player){
  // Prompt the player and input the target items

  cout << "What do you wish to buy? ";
    string item1, item2, item;
      cin >> item1 >> item2;
      item = item1 + " " + item2;

  // Check the cases where the player does not have enough money
  string rejection = "Not enough coins. Try to earn more in the game.";

  // Handle the case when the player want to purchase energy drink
  if (item == "energy drink" || item == "Energy drink") {
    if (player.coins < 20) {
      cout << rejection << endl;
      return;
    }
    if (player.health == 100) {
      cout << "You have not received any injuries. ";
      cout << "Do you still want to purchase energy drink? (yes/no) ";

      string drinkConfirmation;
      cin >> drinkConfirmation;
      
      if (drinkConfirmation == "yes") {
        cout << "You have purchased energy drink." << endl;
	      player.coins -= 20;
	    }
      else if (drinkConfirmation == "no") {
        return;
	    }
      else {
        cout << "Invalid options" << endl;
	    }
    }
    else {
      player.health += 8;
      
      // Maximum hit points is 100
      if (player.health > 100) {
        player.health = 100;
      }

      player.coins -= 20;
      cout << "You have purchased energy drink." << endl;
      cout << "Now you have " << player.health << " HP." << endl;
    }
  }
  // Handle the case when player wnat to be trained
  else if (item == "Body training" || item == "body training") {
    if (player.coins < 30) {
      cout << rejection << endl;
	    return;
	  }
    player.coins -= 30;
    player.health += 15;

    // Maximum hit points is 100
      if (player.health > 100) {
        player.health = 100;
      }
    
    cout << "You have been trained.";
    cout << " Your endurance is now better than ever." << endl;
  }
  // Handle the case when the player want to kill one monster
  else if (item == "monster hunter" || item == "Monster hunter") {
    if (player.coins < 40) {
      cout << rejection << endl;
	    return;
	  }

    if (monsterCount == 0) {
	    cout << "There are no monsters in the maze. Do you still wish to hire a hunter? (yes/no)" << endl;
	    string hunterConfirmation;
	    cin >> hunterConfirmation;

	    if (hunterConfirmation == "yes") {
		    player.coins -= 40;
	      return;
	    }
	    else if (hunterConfirmation == "no") {
		    return;
	    }
    }
    else {
	    player.coins -= 40;
	    monsterCount -= 1;
	    monsterHunt += 1;
      cout << "One monster has been killed" << endl;
    }
  }
  else {
    cout << "Invalid options." << endl;
  }
}

void visitShop(int & monsterHunt, int & monsterCount, playerObject & player, string exitPoint){
  clearscreen();
	
  // Input and print the shop screen
  int shopRowSize = 0, shopColumnSize = 0;
  string filename = "shop.txt", type = "shop";
  string ** shopArray = initPlot(filename, type, shopRowSize, shopColumnSize);
  printPlot(shopArray, shopRowSize, shopColumnSize, exitPoint, false);

  // Ask the player if they want to buy items
  cout << "Welcome to the shop, stranger." << endl;
  sleep(1);
  cout << "You have " << player.coins << " coins left." << endl;
  cout << "Do you wish to buy some goods? (yes/no) ";

  string drinkConfirmation;
  cin >> drinkConfirmation;

  if (drinkConfirmation == "no") {
    cout << "See you soon." << endl;
    deleteArray(shopArray, shopRowSize);
    clearscreen();
    return;
  }

  while (drinkConfirmation != "no") {
    purchaseOptions(monsterHunt, monsterCount, player);
    cout << "Is there anything you still want to buy? (yes/no) ";
    cin >> drinkConfirmation;
  }

  cout << "See you soon." << endl;
  sleep(1);

  // Free memory slots
  deleteArray(shopArray, shopRowSize);

  clearscreen();
}
    
  
