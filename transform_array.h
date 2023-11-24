#include <iostream>
#include <string>
#include "players.h"
#ifndef TRANSFORM_ARRAY_H
#define TRANSFORM_ARRAY_H

void array_size(int &row_size, int &column_size, string filename);
void transform_array(string **&array, int row_length, int column_length, string filename, string type);
void print_plot(string ** array, int row_size, int column_size);
string ** create_plot(string filename, string type, int &row_size, int &column_size);
void delete_array(string **&array, int row_size);
string ** create_plot(string filename, string type, int &row_size, int &column_size);

#endif
