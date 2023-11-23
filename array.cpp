#include <iostream>
#include <string>
#include <fstream>
#include "transform_array.h"
#include "players.h"
#include <sstream>
using namespace std;

// Read the text file size
void array_size(int &row_size, int &column_size, string filename){
  ifstream fin;
  string row;
  column_size = 0;

  // Opens map text file. Return row and column size using pass by reference
  fin.open(filename.c_str());
  if (fin.fail()){
    cout<<"error occurs!"<<endl;
    exit(1);
    }
  while (getline(fin, row)){
    column_size = row.length();
    row_size++;
    }
  fin.close();
  }

// Transform content of text file into a 2D array.
// Function will respond corresponding based on type of text file specified
void transform_array(string **&array, int row_length, int column_length, string filename, string type){
  ifstream fin;
  fin.open(filename.c_str());
  if (fin.fail()){
    cout << "error occurs!" << endl;
    exit(1);
    }

  int array_row=0, array_column=0;
  string row, map_symbol;
  
  // Obtain content of text file line by line
  while (getline(fin, row)){
    // Read every single character and input to array
    for (int i=0; i<column_length; i++){
      map_symbol = row.substr(i,1);  
      array[array_row][i] = map_symbol; 
      }
    array_row++;
    }

  // Calculate player spawn point if the type of text file is maze 
  if (type == "maze"){
  int spawn_row = row_length/2, spawn_column = column_length/2;
  playerObject character = playerObject(spawn_row, spawn_column, true);
  array[spawn_row][spawn_column] = character.avatar;
  }
  fin.close();
  }

  // function to print the array as maze
void print_plot(string ** array, int row_size, int column_size){
  for (int i=0; i<row_size;i++){
    for (int j=0; j<column_size;j++){
      cout << array[i][j];
      }
    cout<< endl;
    }
  }

  

  //function to release memeory location occupied by dynamic array
void delete_array(string **&array, int row_size){
  for (int i=0;i<row_size;i++){
    delete [] array [i];
    }
  delete [] array;
  }


// Function to transform a text file into 2D array using previous functions
string ** create_plot(string filename, string type, int &row_size, int &column_size){
  row_size=0, column_size =0;
  array_size(row_size, column_size, filename);
  string ** array = new string * [row_size];
  for (int i=0; i<row_size;i++){
    array[i] = new string [column_size];
    }
  transform_array(array,row_size, column_size, filename, type);
  return array; 
  }
    







   
