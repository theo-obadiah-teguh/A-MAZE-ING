#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include "transform_array.h"
using namespace std;

void purchase_options(int &coin, int &monster_count, int &bumps, int &maxBumps){
  cout << "What do you wish to buy?" << endl;
  string item_string_1, item_string_2;
  cin >> item_string_1 >> item_string_2;
  string item = item_string_1 + " " + item_string_2;
  string rejection = "Not enough coin. Try to earn more in the game.";
  if (item == "energy drink" || item == "Energy drink"){
    if (coin < 20){
      cout << rejection << endl;
      return;
      }
    if (bumps == 0){
      cout << "You have not received any injuries. ";
      cout << "Do you still want to purchase energy drink? (yes/no)"<<endl;
      string answer;
      cin >> answer;
      if (answer == "yes"){
        cout << "You have purchased energy drink." << endl;
	coin -= 20;
	}
      else if (answer == "no"){
        return;
	}
      else{
        cout << "Invalid options" << endl;
	}
      }
    else {
      bumps -= 1;
      coin -= 20;
      cout << "You have purchased energy drink." << endl;
      }
    }
    else if (item == "Body training" || item == "body training"){
      if (coin < 30){
        cout << rejection << endl;
	return;
	}
      coin -= 30;
      maxBumps += 1;
      cout << "You have been trained.";
      cout << " Your endurance is now better than ever." << endl;
      }
    else if (item == "monster hunter" || item == "Monster hunter"){
      if (coin < 40){
        cout << rejection << endl;
	return;
	}
      if (monster_count == 0){
	      cout << "There is no monsters in the maze. Do you still wish to hire a hunter? (yes/no)" << endl;
	      string answer_2;
	      cin >> answer_2;
	      if (answer_2 == "yes"){
		      coin -= 40;
	              return;
	      }
	      else if (answer_2 == "no"){
		      return;
	      }
      }
      else {
	      coin -= 40;
              cout << "One monster has been killed" << endl;
           }
    }
    else {
      cout << "Invalid options." << endl;
      }
    }

void visiting_shop(int &coin, int &monster_count, int &bumps, int &maxBumps){
  system("cls||clear");
  int shop_row_size = 0, shop_column_size = 0;
  string filename = "shop.txt", type = "shop";
  string ** shop_array = create_plot(filename, type, shop_row_size, shop_column_size);
  print_plot(shop_array, shop_row_size, shop_column_size);
  cout << "Welcome to the shop, stranger." << endl;
  sleep(1);
  cout << "You have " << coin << " coins left." << endl;
  cout << "Do you wish to buy some goods? (yes/no)" << endl;
  string answer;
  cin >> answer;
  if (answer == "no"){
    cout << "See you soon." << endl;
    delete_array(shop_array, shop_row_size);
    return;
    }
  while (answer != "no"){
    purchase_options(coin, monster_count, bumps, maxBumps);
    cout << "Is there anything you still want to buy? (yes/no)" << endl;
    cin >> answer;
    }
  cout << "See you soon." << endl;
  sleep(1);
  delete_array(shop_array, shop_row_size);
  }
    
  
