#include <iostream>
#include <unistd.h>
#include <cctype>
#include "plotting.h" // For the availability of the clearscreen() function
using namespace std;

// Copyright disclaimer, all ASCII art was retrieved from the ASCII Art Archive website
// We will define several images and their respective animation functions below

const char * defeatArt =
"      ,-=-.       ______     _            \n"
"     /  +  \\     />----->  _|1|_         \n"
"     | ~~~ |    // -/- /  |_ H _|         \n"
"     |R.I.P|   //  /  /     |S|           \n"
"\\vV,,|_____|V,//_____/VvV,v,|_|/,,vhjwv/,\n";

const char * victoryArt =
"                                  ___________                                            \n"
"                             .---\'::\'        `---.                                     \n"
"                            (::::::\'              )                                     \n"
"                            |`-----._______.-----\'|                                     \n"
"                            |              :::::::|                                      \n"
"                           .|               ::::::!-.                                    \n"
"                           \\|               :::::/|/                                    \n"
"                            |               ::::::|                                      \n"
"                            | Good Job Traveller :|                                      \n"
"                            | You did great   ::::|                                      \n"
"                            |               ::::::|                                      \n"
"                            |              .::::::|                                      \n"
"                            J              :::::::F                                      \n"
"                             \\            :::::::/                                      \n"
"                              `.        .:::::::'                                        \n"
"                                `-._  .::::::-'                                          \n"
"____________________________________|  \"\"\"|\"_________________________________________\n"
"                                    |  :::|                                              \n"
"                                    F   ::J                                              \n"
"                                   /     ::\\                                            \n"
"                              __.-'      :::`-.__                                        \n"
"                             (_           ::::::_)                                       \n"
"                               `\"\"\"---------\"\"\"'                                   \n";

// Editing notice for the welcome art
// There are 40 character slots for the title (see example below)
//       Welcome to Dungeon Explorer!     |

const char * welcomeArt = 

"               )\\         O_._._._A_._._._O         /(               \n"
"                \\`--.___,\'=================`.___,--\'/                \n"
"                 \\`--._.__                 __._,--\'/                 \n"
"                   \\  ,. l`~~~~~~~~~~~~~~~\'l ,.  /                   \n"
"       __            \\||(_)!_!_!_.-._!_!_!(_)||/            __       \n"
"       \\`-.__        ||_|____!!_|;|_!!____|_||        __,-\'//       \n"
"        \\    `==---=\'-----------\'=\'-----------`=---==\'    //        \n"
"        | `--.       Welcome to Dungeon Explorer!     ,--\' |        \n"
"         \\  ,.`~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\',.  /         \n"
"           \\||  ____,-------._,-------._,-------.____  ||/           \n"
"            ||\\|___!`=======\"!`=======\"!`=======\"!___|/||            \n"
"            || |---||--------||-| | |-!!--------||---| ||            \n"
"  __O_____O_ll_lO_____O_____O|| |\'|\'| ||O_____O_____Ol_ll_O_____O__  \n"
"  o H o o H o o H o o H o o |-----------| o o H o o H o o H o o H o  \n"
" ___H_____H_____H_____H____O =========== O____H_____H_____H_____H___ \n"
"                          /|=============|\\                          \n"
"()______()______()______() \'==== +-+ ====\' ()______()______()______()\n"
"||{_}{_}||{_}{_}||{_}{_}/| ===== |_| ===== |\\{_}{_}||{_}{_}||{_}{_}||\n"
"||      ||      ||     / |==== s(   )s ====| \\     ||      ||      ||\n"
"======================()  =================  ()======================\n"
"----------------------/| ------------------- |\\----------------------\n"
"                     / |---------------------| \\                     \n"
"-\'--\'--\'           ()  \'---------------------\'  ()                   \n"
"                   /| ------------------------- |\\    --\'--\'--\'      \n"
"       --\'--\'     / |---------------------------| \\    \'--\'          \n"
"                ()  |___________________________|  ()           \'--\'-\n"
"  --\'-          /| _______________________________  |\\               \n"
" --\'           / |__________________________________| \\              \n";

const char* exitArt = 
"     _         \n"
"   _| |        \n"
" _| | |        \n"
"| | | |        \n"
"| | | | __     \n"
"| | | |/  \\   \n"
"|       /\\ \\ \n"
"|      /  \\/  \n"
"|      \\  /\\ \n"
"|       \\/ /  \n"
" \\        /   \n"
"  |     /      \n"
"  |    |       \n";

// Below are the animation scripts

// An animation script for when the player loses the game
void defeatAnimation() {
  clearscreen();

  cout << "Oh no..." << endl;
  sleep(2);

  cout << "You have lost the game!" << endl;
  cout << endl;
  sleep(2);

  cout << defeatArt;
  cout << endl;
  sleep(2);

  cout << "You will be redirected to the main menu in a few seconds..." << endl;
  sleep(3);
}

// When the player quits the game
void exitAnimation() {
  clearscreen();

  cout << "See you next time, traveller!" << endl;
  sleep(1);

  cout << exitArt << endl;
}

bool firstPlay = true;

// Main menu function for the game

void startMenu() {  
  clearscreen();
  string answer;
  
  // Keep handling for player input until he/she want to enter the maze game or exit
  while (true) {
    //cout << i << endl;
    int count = 0;
    cout << "1. Start Game" << endl;
    cout << "2. Rules" << endl;
    cout << "3. Credits" << endl;
    cout << "4. Quit" << endl;

    string prompt;
    cout << "Please PRESS a number (1-4): ";
    cin >> prompt;

    // Check if the input is indeed a number
    if (!all_of(prompt.begin(), prompt.end(), ::isdigit)) {
      clearscreen();
      continue;
    }

    // Convert string input to integer
    int choice = stoi(prompt);
    if (choice == 1) {
      return;
    }

    // Handle the cases when the player does not want to play the main game yet
	  if (!isdigit(choice))
    switch (choice) {
      case 2:
        while (true) {
          // Display the rules
          clearscreen();
          cout << "--------------------------------------------------------------------------------------- " << endl;
          cout << "                                         Rules                                          " << endl;
          cout << "--------------------------------------------------------------------------------------- " << endl;
          cout << " 1. Choose a difficulty level: easy, medium, or hard" << endl;
          cout << " 2. Navigate the maze with the 'w'(up), 'a'(left), 's'(down), 'd'(right) keys" << endl;
          cout << " 3. Select how many steps to take" << endl;
          cout << " 4. Find the exit point indicated by the number 1, 2, 3 or 4" << endl;
          cout << " 5. Avoid obstacles '#' and walls '|' to not lose health points" << endl;
          cout << " 6. Watch out for the monsters!" << endl;
          cout << " 7. Teleport 'T' to a random location if you wish, or eat them if you have enough points" << endl;
          cout << " 8. Go to shops '$' to purchase items to help you survive!" << endl;
          cout << "--------------------------------------------------------------------------------------- " << endl;
          cout << "PRESS q to exit rules display: ";
	        cin >> answer;
	        if (answer == "q") {
	          clearscreen();
	          break;
	        }
        }
	      break;
      case 3:
        while (true) {
          clearscreen();
          cout << "---------------------------------------" << endl;
          cout << "                Credits                " << endl;
          cout << "---------------------------------------" << endl;
          cout << "        Name          |     UID        " << endl;
          cout << " Bhardwaj Aryaman     |  3035858755    " << endl;
          cout << " Fok Po Hin           |  3036062262    " << endl;
          cout << " Lai Wan Ching Anson  |  3036067676    " << endl;
          cout << " Lee Ka Ka            |  3035921174    " << endl;
          cout << " Teguh Theo Obadiah   |  3035898872    " << endl;   
          cout << "---------------------------------------" << endl;
          cout << "PRESS q to exit credit screen: ";
	        cin >> answer;
	        if(answer == "q") {
	          clearscreen();
	          break;
	        }
        }
	      break;
      case 4:
        // Quit the game
        exitAnimation();
        exit(0);
	      break;
      default:
        // Invalid choice
        clearscreen();
	      break;
    }
  }
}

// An animation script for when the player wins the game
void victoryAnimation() {
  clearscreen();

  cout << "Congratulations." << endl;
  sleep(2);

  cout << "You have won the game!" << endl;
  cout << endl;
  sleep(2);

  cout << victoryArt;
  cout << endl;
  sleep(2);

  cout << "You will be redirected to the main menu in a few seconds..." << endl;
  sleep(3);
	
}

// An animation script for when the player starts the game

void welcomeAnimation() {
  clearscreen();
  cout << "A long... long... time ago..." << endl;
  sleep(1);

  cout << "In the middle of a forest... in ancient China..." << endl;
  sleep(1);

  cout << "There was a dungeon..." << endl;
  cout << endl;
  sleep(1);
  
  cout << welcomeArt << endl;
  sleep(3);
  clearscreen();

  sleep(1);

  startMenu();
}

