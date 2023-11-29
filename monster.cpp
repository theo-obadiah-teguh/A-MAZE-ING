#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
#include <vector>
#include "players.h"



struct monsterObject{
    int direction;
    int vertical_ax;
    int horizontal_ax;
};
vector<monsterObject *> monster;
//updated monster_count var
int monster_count;

//void -> int
void monster_no(string difficulty, int &monster_count){
    if (difficulty == "easy") {
      monster_count = 3;
    }
    else if (difficulty == "medium") {
     monster_count = 5;
    }
    else if (difficulty == "hard") {
      monster_count = 7;
    }
    else{
        monster_count = 0;
    }
}

void create_monsters(int monster_count){
    for(int i = 0; i < monster_count; i++){
        monster.push_back(new monsterObject);
    }
}

//vector<monsterObject *> monster;
/*
for(int i = 0; i < monster_count; i++){
    monster.push_back(new monsterObject);
}
 */

void hunt_monster(){
    monster.pop_back();
    return;
}

void monster_dir(playerObject player){
    time_t _time=time(nullptr);
    srand(static_cast<unsigned>(_time));
    
    for (int i = 0; i < monster.size(); i++){
        cout << "loop" << endl;
        time_t _time=time(nullptr);
        // 1 is up, 2 is right, 3 is down, 4 is left
        if (monster[i]->vertical_ax - player.vertical <= 0 ){
            if (monster[i]->horizontal_ax - player.horizontal >= 0){
                monster[i]->direction=rand()%2+3;
                cout << "monster[" << i << "] direction is " << monster[i]->direction;
            } else {
                monster[i]->direction=rand()%2+2;
                cout << "monster[" << i << "] direction is " << monster[i]->direction;
            }
        } else {
            if (monster[i]->horizontal_ax - player.horizontal <= 0) {
                monster[i]->direction=rand()%2+1;
                cout << "monster[" << i << "] direction is " << monster[i]->direction;
            } else {
                monster[i]->direction=(rand() % 2 == 0) ? 1 : 4;
                cout << "monster[" << i << "] direction is " << monster[i]->direction;
            }
        }
    }
}
/*
void init(int rowSize, int columnSize, string ** myPlot, int monster_count){
    time_t _time=time(nullptr);
    srand(static_cast<unsigned>(_time));
    for (int i=0;i<monster_count;i++){
        monster[i]->vertical_ax=rand()%rowSize;
        monster[i]->horizontal_ax=rand()%columnSize;
        if (myPlot[monster[i]->vertical_ax][monster[i]->horizontal_ax]==" "){
            myPlot[monster[i]->vertical_ax][monster[i]->horizontal_ax]="☠";
        }
        else{
            if (myPlot[monster[i]->vertical_ax][monster[i]->horizontal_ax]!=" "){
                monster[i]->vertical_ax-=1;
                myPlot[monster[i]->vertical_ax][monster[i]->horizontal_ax]="☠";
            }
            else{
                if (myPlot[monster[i]->vertical_ax][monster[i]->horizontal_ax]=="|" && myPlot[monster[i]->vertical_ax][monster[i]->horizontal_ax-1]=="*" && myPlot[monster[i]->vertical_ax][monster[i]->horizontal_ax+1]==" "){
                    monster[i]->horizontal_ax+=1;
                    myPlot[monster[i]->vertical_ax][monster[i]->horizontal_ax]="☠";
                }
                else if (myPlot[monster[i]->vertical_ax][monster[i]->horizontal_ax]=="|" && myPlot[monster[i]->vertical_ax][monster[i]->horizontal_ax+1]=="*" && myPlot[monster[i]->vertical_ax][monster[i]->horizontal_ax-1]==" "){
                    monster[i]->horizontal_ax-=1;
                    myPlot[monster[i]->vertical_ax][monster[i]->horizontal_ax]="☠";
                }
                else{
                    do {
                        monster[i]->vertical_ax=rand()%rowSize;
                        monster[i]->horizontal_ax=rand()%columnSize;
                    }
                    while(myPlot[monster[i]->vertical_ax][monster[i]->horizontal_ax]!=" ");
                }
            }
        }
    }
}
 */

void init(int rowSize, int columnSize, string ** myPlot, int monster_count){
    time_t _time=time(nullptr);
    srand(static_cast<unsigned>(_time));
    for (int i=0;i<monster_count;i++){
        monster[i]->vertical_ax=rand()%rowSize;
        monster[i]->horizontal_ax=rand()%columnSize;
        if (myPlot[monster[i]->vertical_ax][monster[i]->horizontal_ax]==" "){
            myPlot[monster[i]->vertical_ax][monster[i]->horizontal_ax]="☠";
        }
        else{
            if (myPlot[monster[i]->vertical_ax][monster[i]->horizontal_ax]!=" "){
                monster[i]->vertical_ax-=1;
                myPlot[monster[i]->vertical_ax][monster[i]->horizontal_ax]="☠";
            }
            else{
                if (myPlot[monster[i]->vertical_ax][monster[i]->horizontal_ax]=="|" && myPlot[monster[i]->vertical_ax][monster[i]->horizontal_ax-1]=="*" && myPlot[monster[i]->vertical_ax][monster[i]->horizontal_ax+1]==" "){
                    monster[i]->horizontal_ax+=1;
                    myPlot[monster[i]->vertical_ax][monster[i]->horizontal_ax]="☠";
                }
                else if (myPlot[monster[i]->vertical_ax][monster[i]->horizontal_ax]=="|" && myPlot[monster[i]->vertical_ax][monster[i]->horizontal_ax+1]=="*" && myPlot[monster[i]->vertical_ax][monster[i]->horizontal_ax-1]==" "){
                    monster[i]->horizontal_ax-=1;
                    myPlot[monster[i]->vertical_ax][monster[i]->horizontal_ax]="☠";
                }
                else{
                    do {
                        monster[i]->vertical_ax=rand()%rowSize;
                        monster[i]->horizontal_ax=rand()%columnSize;
                    }
                    while(myPlot[monster[i]->vertical_ax][monster[i]->horizontal_ax]!=" ");
                }
            }
        }
    }
}


//check validity (make sure the ghost will not out of boundary)
    //1st para  monster_count-> i
bool check_valid(int i, int &monster_steps, string ** myPlot, int rowSize, int columnSize){
    //iterate over all monsters
    //for (int i=0;i<monster_count;i++) {
//updated plotdimension -> rowSize/columnSize
        //vertical movement
        if (monster[i]->direction == 1)  {
            if (monster[i]->vertical_ax + monster_steps <= rowSize) {
                for (int a = 0;a < monster_steps;a++) {
                    /*
                    if (myPlot[monster[i]->vertical_ax-1-a][monster[i]->horizontal_ax] == "|" || myPlot[monster[i]->vertical_ax-1-a][monster[i]->horizontal_ax] == "*") {
                        monster_steps++;
                    }
                     */
                    if (myPlot[monster[i]->vertical_ax-1-a][monster[i]->horizontal_ax] != " ") {
                        monster_steps++;
                    }
                }
                if (monster[i]->vertical_ax + monster_steps <= rowSize) {
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
        else if (monster[i]->direction == 3) {
            if (monster[i]->vertical_ax - monster_steps >= 0) {
                for (int b = 0;b < monster_steps;b++) {
                    /*
                    if (myPlot[monster[i]->vertical_ax+1+b][monster[i]->horizontal_ax] == "|" || myPlot[monster[i]->vertical_ax+1+b][monster[i]->horizontal_ax] == "*") {
                        monster_steps++;
                    }
                     */
                    if (myPlot[monster[i]->vertical_ax+1+b][monster[i]->horizontal_ax] != " ") {
                        monster_steps++;
                    }
                }
                if (monster[i]->vertical_ax - monster_steps >= 0) {
                    return true;
                }
                else {
                    return false;
                }
            }
            else {
                return false;
            }

        //horizontal movement
        }
        else if (monster[i]->direction == 2) {
            if (monster[i]->horizontal_ax + monster_steps <= columnSize) {
                for (int c = 0; c < monster_steps; c++) {
                    /*
                     if (myPlot[monster[i]->vertical_ax][monster[i]->horizontal_ax+1+c] == "*" || myPlot[monster[i]->vertical_ax][monster[i]->horizontal_ax+1+c] == "|") {
                     monster_steps++;
                     }
                     */
                    if (myPlot[monster[i]->vertical_ax][monster[i]->horizontal_ax+1+c] != " ")
                        monster_steps++;
                }
                    
                    if (monster[i]->horizontal_ax + monster_steps <= columnSize)
                        return true;
                    
                    else
                        return false;
                }
                else {
                    return false;
                }
            }
        else if (monster[i]->direction == 4) {
            if (monster[i]->horizontal_ax - monster_steps >= 0) {
                for (int d = 0;d < monster_steps;d++) {
                    /*
                    if (myPlot[monster[i]->vertical_ax][monster[i]->horizontal_ax-1-d] == "*" || myPlot[monster[i]->vertical_ax][monster[i]->horizontal_ax-1-d] == "|") {
                        monster_steps++;
                    }
                     */
                    if (myPlot[monster[i]->vertical_ax][monster[i]->horizontal_ax-1-d] != " ") {
                        monster_steps++;
                    }
                }
                if (monster[i]->horizontal_ax - monster_steps >= 0) {
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
    //}
    return false;
}

    //determine how many steps the monster will take
void monster_steps(string ** myPlot, int rowSize, int columnSize){
    time_t _time=time(nullptr);
    srand(static_cast<unsigned>(_time));
    for (int i=0;i<monster.size();i++){
        time_t _time=time(nullptr);
        int monster_steps=rand()%4+1;
        
        if(check_valid(i, monster_steps, myPlot, rowSize, columnSize)==true){
            //code to move monster
            if (monster[i]->direction==1){
                myPlot[monster[i]->vertical_ax][monster[i]->horizontal_ax]=" ";
                monster[i]->vertical_ax-=monster_steps;
                myPlot[monster[i]->vertical_ax][monster[i]->horizontal_ax]="☠";
            }
            else if (monster[i]->direction==2){
                myPlot[monster[i]->vertical_ax][monster[i]->horizontal_ax]=" ";
                monster[i]->horizontal_ax+=monster_steps;
                myPlot[monster[i]->vertical_ax][monster[i]->horizontal_ax]="☠";
            }
            else if (monster[i]->direction==3){
                myPlot[monster[i]->vertical_ax][monster[i]->horizontal_ax]=" ";
                monster[i]->vertical_ax+=monster_steps;
                myPlot[monster[i]->vertical_ax][monster[i]->horizontal_ax]="☠";
            }
            else{
                myPlot[monster[i]->vertical_ax][monster[i]->horizontal_ax]=" ";
                monster[i]->horizontal_ax-=monster_steps;
                myPlot[monster[i]->vertical_ax][monster[i]->horizontal_ax]="☠";
            }
            //return;
        }
            else{
                //call back function and try until all moves are valid
                do {
                    monster_steps=rand()%4+1;
                } while (check_valid(i, monster_steps, myPlot, rowSize, columnSize)==false);
                //return;
            }
            
        }
    }
    

