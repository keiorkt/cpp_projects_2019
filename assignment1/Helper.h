#ifndef HELPER_H
#define HELPER_H

#include <iostream>
#include <fstream>
#include "Todo.h"
using namespace std;

Stone switch_player(Stone p);
void initialize_board(Stone board[][19]);
void read_file(Stone board[][19], int record[][2], int& counter, int& max_steps, const char filename[]);
void write_file(const int record[][2], const int counter, const int max_steps);
char translate(Stone cell);
void display_board(const Stone board[][19]);
void show_options(Stone player, int counter, int max_steps);
void get_operation(char operation, Stone board[][19]);


#endif /* HELPER_H */