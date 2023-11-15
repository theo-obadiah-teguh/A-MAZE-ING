#include <iostream>
using namespace std;
#include <cstdlib>
#include <ctime>

//determine direction of the ghost (draft)
//currently 4 direction but later should calculate the distance and then set randomization of 2 only
int direction(){
    time_t _time=time(nullptr);
    srand(static_cast<unsigned>(_time));
    for (int i=0;i<3;i++){
        time_t _time=time(nullptr);
        int _dir=rand()%4+1;
        //ghost[i]=_dir;
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
    //code
}
