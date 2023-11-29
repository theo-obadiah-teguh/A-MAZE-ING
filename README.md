# group-110
A private repository for creating a text-based game in C++. The is project part COMP2113: Programming Technologies by the University of Hong Kong.

## A-MAZE-ING

### Our Group Members and UIDs

Bhardwaj, Aryaman       3035858755\
Fok, Po Hin 				    3036062262\
Lai, Wan Ching Anson 		3036067676\
Lee, Ka Ka 				      3035921174\
Teguh, Theo Obadiah 		3035898872

---

### Game Description
<div style="text-align: right">A-MAZE-ING: A thrilling single-player, text-based game awaits you in the depths of your local terminal. Prepare to embark on an epic adventure as you find yourself transported to an ancient Chinese dungeon maze, where your ultimate goal is to find a way out!</div> 

***But beware! The labyrinth is teeming with peril, and you'll encounter a host of dangers along the way.***

<p style='text-align: justify;'> Keep a watchful eye for the hungry ghosts (鬼 gwai2) that lurk in the shadows, their ethereal forms capable of passing through walls, teleporting, and relentlessly pursuing you. Take caution not to unwittingly stumble into unbreakable walls, as they are infused with a mystical poison that can inflict harm. Devise clever strategies to navigate teleporters, overcome obstacles, and reach the exit with utmost swiftness, or alternatively, muster your courage to confront the menacing monsters head-on, deftly leaping over obstacles in your path.</p>

Will you emerge victorious, escaping the clutches of the treacherous maze and claiming a glorious prize? Or will you find yourself trapped, with no escape in sight? The outcome rests solely in your hands, as you seize control of your destiny!

---

### Game Rules
1. Choose a difficulty level: easy, medium, or hard.
1. ‘☺’ is the player avatar, while ‘☠’ is the monster avatar.
1. The player will spawn in the centre of the maze, whilst monsters will spawn randomly in the maze.
1. Every maze has four exits, but only one will be randomly chosen as the road to victory. This exit will be shown on top of the maze.
1. The player will start with 100 HP, 150 coins, and 5 chances to avoid teleporting.
1. ‘$’ is the shop, the player can visit it and purchase items if the player wants.
1. ‘#’ is the obstacle, when the player hits the obstacle, 2 HP will be deducted, and the obstacle will be removed.
1. Walls are denoted by ‘|’, ‘-’, and ‘*’. If the player hits them, 5 HP will be deducted, and they’re avatar will move back one step.
1. ‘T’ is the teleporter and it will teleport the player randomly. The player has 5 chances to avoid the teleporters by eating it.

---

### List of Features and Fulfilment of Task Requirements
#### Coding Element 1: *Generation of random game sets or events*
All three mazes each have four exits. When a player enters the maze, the program will randomly choose one exit to be assigned as the winning condition for the game. Additionally, obstacles, teleporters, and monsters are all spawned randomly throughout the maze. This was implemented using the in-built random function.

#### Coding Element 2: *Data structures for storing game status*
Mazes of three different difficulties (different sizes) have been prepared and stored  into a 2D dynamic array of strings where its contents get updated as the player moves. The location, avatar, health points, and eat points are saved in a custom struct called playerObject. Similarly, each ghost/monster is represented by a monsterObject which includes its location and the next direction of its movement. The monsters are programmed to move towards the player's location/index in the array. The number of health points, coins, and eat points on the screen is updated every time a player runs into an obstacle, shop or teleporter. If obstacles, shops or teleporters have been encountered they disappear from the maze.

#### Coding Element 3: *Dynamic memory management*
The 2D arrays storing constructor characters of the maze and shop are created dynamically with sizes determined at runtime. This dynamic 2D array is actually an array of pointers to pointers. The size of the 2D array for the maze is based on the chosen difficulty level, and it will be deleted when the player exits a game and returns to the main menu. On the other hand, each time a player encounters a shop, the shop text file will be transformed into a 2D array and deleted every time after the player exits the shop. 

#### Coding Element 4: *File input/output*
All three mazes are handcrafted text files. When we prompt the player for the difficulty level, the program will input the maze according to the chosen level.

#### Coding Element 5: *Program codes in multiple files*
We have separated the program into different groups based on their functionality. We have files specifically for the playerObject, monsterObject, the shop feature, and aesthetics which include the ASCII art and main menu screen. Each of these additions are organised within their own header files and implemented in the main program as needed.

---

### Use of Non-Standard Libraries
There were no non-standard libraries used in the creation of this game.

