#include <iostream>
#include <unistd.h>
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
  system("cls||clear");

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

// An animation script for when the player wins the game
void victoryAnimation() {
  system("cls||clear");

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

//When the player quits the game
void exitAnimation() {
  system("cls||clear");

  cout << "See you next time, traveller!" << endl;
  sleep(1);

  cout << exitArt << endl;
}

// An animation script for when the player starts the game
void welcomeAnimation() {
  system("cls||clear");
  cout << "A long... long... time ago..." << endl;
  sleep(2);

  cout << "In the middle of a forest... in ancient China..." << endl;
  sleep(2);

  cout << "There was a dungeon..." << endl;
  cout << endl;
  sleep(1);

  cout << welcomeArt << endl;
  sleep(1);

  cout << "1. Start Game" << endl;
  cout << "2. Rules" << endl;
  cout << "3. Quit" << endl;

  int choice;
  cout << "Enter your choice (1, 2, 3): ";
  cin >> choice;

  switch (choice){
    case 1:
          //Start the game
          break;
    case 2:
          //Display the rules
          cout << "------------------------------------------------------------ " << endl;
          cout << "Rules:" << endl;
          cout << "Navigate the maze through the arrow keys 'w' 'a' 's' 'd' " << endl;
          cout << "Select how many steps to take" << endl;
          cout << "Find the exit point indicated by the number 1, 2, 3 or 4" << endl;
          cout << "Avoid obstacles # and walls |" << endl;
          cout << "Teleport T to a random location if you wish" << endl;
          cout << "Collect coins $ along the way" << endl;
          cout << "------------------------------------------------------------ " << endl;
          break;
    case 3:
          //Quit the game
          exitAnimation();
          exit(0);
    default:
          //Invalid choice
          cout << "Invalid choice. Please try again." << endl;
          break;
  }
}

