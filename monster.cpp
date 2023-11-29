#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
#include <vector>
#include "players.h"
#include "monster.h"

vector<monsterObject *> monster;
//updated monster_count var
int monsterCount;

void monsterNo(string difficulty, int &monsterCount){
    if (difficulty == "easy") {
      monsterCount = 1;
    }
    else if (difficulty == "medium") {
     monsterCount = 3;
    }
    else if (difficulty == "hard") {
      monsterCount = 5;
    }
    else{
        monsterCount = 0;
    }
}

void createMonsters(int monsterCount){
    for(int i = 0; i < monsterCount; ++i){
        monster.push_back(new monsterObject);
    }
}

void huntMonster(string ** array){
    int location = monster.size();
    myPlot[monster[location-1]->vertical_ax][[monster[location-1]->horizontal_ax]] = ' ';
    monster.pop_back();
    return;
}

void monsterDir(playerObject player){
    time_t _time=time(nullptr);
    srand(static_cast<unsigned>(_time));
    
    for (int i = 0; i < monster.size(); ++i){
        cout << "loop" << endl;
        time_t _time=time(nullptr);
        // 1 is up, 2 is right, 3 is down, 4 is left
        if (monster[i]->vertical_ax - player.vertical <= 0 ){
            if (monster[i]->horizontal_ax - player.horizontal >= 0){
                monster[i]->direction=rand()%2+3;
            } else {
                monster[i]->direction=rand()%2+2;
            }
        } else {
            if (monster[i]->horizontal_ax - player.horizontal <= 0) {
                monster[i]->direction=rand()%2+1;
            } else {
                monster[i]->direction=(rand() % 2 == 0) ? 1 : 4;
            }
        }
    }
}

void init(int rowSize, int columnSize, string ** myPlot, int monsterCount){
    time_t _time=time(nullptr);
    srand(static_cast<unsigned>(_time));
    for (int i=0;i<monsterCount;++i){
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
bool checkValid(int i, int &monsterSteps, string ** myPlot, int rowSize, int columnSize){
    //iterate over all monsters
    //for (int i=0;i<monster_count;i++) {
//updated plotdimension -> rowSize/columnSize
        //vertical movement
        if (monster[i]->direction == 1)  {
            if (monster[i]->vertical_ax + monsterSteps <= rowSize-1) {
                for (int a = 0;a < monsterSteps;++a) {
                    /*
                    if (myPlot[monster[i]->vertical_ax-1-a][monster[i]->horizontal_ax] == "|" || myPlot[monster[i]->vertical_ax-1-a][monster[i]->horizontal_ax] == "*") {
                        monsterSteps++;
                    }
                     */
                    if (myPlot[monster[i]->vertical_ax-1-a][monster[i]->horizontal_ax] != " ") {
                        monsterSteps++;
                    }
                }
                if (monster[i]->vertical_ax + monsterSteps <= rowSize-1) {
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
            if (monster[i]->vertical_ax - monsterSteps >= 0) {
                for (int b = 0;b < monsterSteps;++b) {
                    /*
                    if (myPlot[monster[i]->vertical_ax+1+b][monster[i]->horizontal_ax] == "|" || myPlot[monster[i]->vertical_ax+1+b][monster[i]->horizontal_ax] == "*") {
                        monsterSteps++;
                    }
                     */
                    if (myPlot[monster[i]->vertical_ax+1+b][monster[i]->horizontal_ax] != " ") {
                        monsterSteps++;
                    }
                }
                if (monster[i]->vertical_ax - monsterSteps >= 0) {
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
            if (monster[i]->horizontal_ax + monsterSteps <= columnSize-1) {
                for (int c = 0; c < monsterSteps; ++c) {
                    /*
                     if (myPlot[monster[i]->vertical_ax][monster[i]->horizontal_ax+1+c] == "*" || myPlot[monster[i]->vertical_ax][monster[i]->horizontal_ax+1+c] == "|") {
                     monsterSteps++;
                     }
                     */
                    if (myPlot[monster[i]->vertical_ax][monster[i]->horizontal_ax+1+c] != " ")
                        monsterSteps++;
                }
                    
                    if (monster[i]->horizontal_ax + monsterSteps <= columnSize-1)
                        return true;
                    
                    else
                        return false;
                }
                else {
                    return false;
                }
            }
        else if (monster[i]->direction == 4) {
            if (monster[i]->horizontal_ax - monsterSteps >= 0) {
                for (int d = 0;d < monsterSteps;++d) {
                    /*
                    if (myPlot[monster[i]->vertical_ax][monster[i]->horizontal_ax-1-d] == "*" || myPlot[monster[i]->vertical_ax][monster[i]->horizontal_ax-1-d] == "|") {
                        monsterSteps++;
                    }
                     */
                    if (myPlot[monster[i]->vertical_ax][monster[i]->horizontal_ax-1-d] != " ") {
                        monsterSteps++;
                    }
                }
                if (monster[i]->horizontal_ax - monsterSteps >= 0) {
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
void monsterSteps(string ** myPlot, int rowSize, int columnSize){
    time_t _time=time(nullptr);
    srand(static_cast<unsigned>(_time));
    for (int i=0;i<monster.size();++i){
        time_t _time=time(nullptr);
        int monsterSteps=rand()%4+1;
        
        if(checkValid(i, monsterSteps, myPlot, rowSize, columnSize)==true){
            //code to move monster
            if (monster[i]->direction==1){
                myPlot[monster[i]->vertical_ax][monster[i]->horizontal_ax]=" ";
                monster[i]->vertical_ax-=monsterSteps;
                myPlot[monster[i]->vertical_ax][monster[i]->horizontal_ax]="☠";
            }
            else if (monster[i]->direction==2){
                myPlot[monster[i]->vertical_ax][monster[i]->horizontal_ax]=" ";
                monster[i]->horizontal_ax+=monsterSteps;
                myPlot[monster[i]->vertical_ax][monster[i]->horizontal_ax]="☠";
            }
            else if (monster[i]->direction==3){
                myPlot[monster[i]->vertical_ax][monster[i]->horizontal_ax]=" ";
                monster[i]->vertical_ax+=monsterSteps;
                myPlot[monster[i]->vertical_ax][monster[i]->horizontal_ax]="☠";
            }
            else{
                myPlot[monster[i]->vertical_ax][monster[i]->horizontal_ax]=" ";
                monster[i]->horizontal_ax-=monsterSteps;
                myPlot[monster[i]->vertical_ax][monster[i]->horizontal_ax]="☠";
            }
            //return;
        }
            else{
                //call back function and try until all moves are valid
                do {
                    monsterSteps=rand()%4+1;
                } while (checkValid(i, monsterSteps, myPlot, rowSize, columnSize)==false);
                //return;
            }
            
        }
    }
    

