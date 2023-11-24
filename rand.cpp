#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

/*
struct ghostObject={
    int direction;
    int vertical_ax;
    int horizontal_ax;
}
*/

//determine direction of the ghost (draft)
//currently 4 direction but later we should calculate the distance and then set randomisation of 2 only
int direction(){
    time_t _time=time(nullptr);
    srand(static_cast<unsigned>(_time));
    //assume 3 ghost first, later change to the number of ghost dynamically
    for (int i=0;i<3;i++){
        time_t _time=time(nullptr);
        // 1 is up, 2 is right, 3 is down, 4 is left
        if (ghostObject.vertical_ax - playerObject.vertical >= 0 ){
            if (ghostObject.horizontal_ax - playerObject.horizontal >= 0){
                int _dir=rand()%2+3
            } else {
                int _dir=rand()%2+2
            }
        } else {
            if (ghostObject.horizontal_ax - playerObject.horizontal >= 0) {
                int _dir=rand()%2+1
            } else {
                int _dir=(rand() % 2 == 0) ? 1 : 4;
            }
        }
        srand(static_cast<unsigned>(_time+1));
        //ghost[i].direction=_dir;
}        

//determine how many steps the ghost will take
int steps(){
    time_t _time=time(nullptr);
    srand(static_cast<unsigned>(_time));
    for (int i=0;i<3;i++){
        time_t _time=time(nullptr);
        int _steps=rand()%4+1;
        /*
        if(check_valid(i, _steps)){
            //code to move ghost
        }
        else{
            //call back function and try until all moves are valid
            step()
        }
        */
}

//check validity (make sure the ghost will not out of boundary)
bool check_valid(int ghost_no, int steps){
    //iterate over all ghosts
    for (int i=0;i<ghost_no;i++) {

        //vertical movement
        if (ghostObject.direction == 1)  {
            if (ghostObject.vertical_ax + steps =< plotDimension) {
                for (int a = 0;a < steps;a++) {
                    if (myPlot[ghostObject.vertical_ax-1-a][ghostObject.horizontal_ax] == '_') {
                        steps++
                    }    
                }
                if (ghostObject.vertical_ax + steps =< plotDimension) {
                    return TRUE
                } else {
                    return FALSE
                }
            } else {
                return FALSE
            }
        } else if (ghostObject.direction == 3) {
            if (ghostObject.vertical_ax - steps >= 0) {
                for (int b = 0;b < steps;b++) {
                    if (myPlot[ghostObject.vertical_ax+1+b][ghostObject.horizontal_ax] == '_') {
                        steps++
                    }    
                }
                if (ghostObject.vertical_ax - steps >= 0) {
                    return TRUE
                } else {
                    return FALSE
                }
            } else {
                return FALSE
            }

        //horizontal movement
        } else if (ghostObject.direction == 2) {
            if (ghostObject.horizontal_ax + steps =< plotDimension) {
                for (int c = 0;c < steps;c++) {
                    if (myPlot[ghostObject.vertical_ax][ghostObject.horizontal_ax+1+c] == '|') {
                        steps++
                    }
                }
                if (ghostObject.horizontal_ax + steps =< plotDimension) {
                    return TRUE
                } else {
                    return FALSE
                }
            } else {
                return FALSE
            }
        } else if (ghostObject.direction == 4) {
            if (ghostObject.horizontal_ax - steps >= 0) {
                for (int d = 0;d < steps;d++) {
                    if (myPlot[ghostObject.vertical_ax][ghostObject.horizontal_ax-1-d] == '|') {
                        steps++
                    }
                }
                if (ghostObject.horizontal_ax - steps >= 0) {
                    return TRUE
                } else {
                    return FALSE
                }
            } else {
                return FALSE
            }
        }
    }       
}
